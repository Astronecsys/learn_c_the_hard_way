#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Address {
    int id;
    int set;
    char *name;
    char *email;
};

struct Database {
    int max_data;
    int max_rows;
    struct Address *rows;
};

struct Connection {
    FILE *file;
    struct Database *db;
};

void Database_close(struct Connection *conn);

void die(struct Connection *conn, const char *message) {
    if (conn) {
        Database_close(conn);
    }
    if (errno) {
        perror(message);
    } else {
        printf("ERROR: %s\n", message);
    }
    exit(1);
}

void Address_print(struct Address *addr) {
    printf("%d %s %s\n", addr->id, addr->name, addr->email);
}

void Database_load(struct Connection *conn) {
    FILE *file = conn->file;
    struct Database *db = conn->db;

    if (fread(&db->max_rows, sizeof(int), 1, file) != 1)
        die(conn, "Failed to read max_rows");
    if (fread(&db->max_data, sizeof(int), 1, file) != 1)
        die(conn, "Failed to read max_data");

    db->rows = malloc(sizeof(struct Address) * db->max_rows);
    if (!db->rows)
        die(conn, "Memory error on db->rows");

    for (int i = 0; i < db->max_rows; ++i) {
        struct Address *addr = &db->rows[i];

        if (fread(&addr->id, sizeof(int), 1, file) != 1)
            die(conn, "Failed to read id");
        if (fread(&addr->set, sizeof(int), 1, file) != 1)
            die(conn, "Failed to read set");

        addr->name = malloc(sizeof(char) * db->max_data);
        if (!addr->name)
            die(conn, "Memory error on name");
        if (fread(addr->name, sizeof(char), db->max_data, file) != db->max_data)
            die(conn, "Failed to read name");

        addr->email = malloc(sizeof(char) * db->max_data);
        if (!addr->email)
            die(conn, "Memory error on email");
        if (fread(addr->email, sizeof(char), db->max_data, file) !=
            db->max_data)
            die(conn, "Failed to read email");
    }
}

struct Connection *Database_open(const char *filename, char mode) {
    struct Connection *conn = malloc(sizeof(struct Connection));
    if (!conn)
        die(conn, "Memory error");

    conn->db = calloc(1, sizeof(struct Database));
    if (!conn->db)
        die(conn, "Memory error");

    if (mode == 'c') {
        conn->file = fopen(filename, "w");
    } else {
        conn->file = fopen(filename, "r+");
        if (conn->file) {
            Database_load(conn);
        }
    }
    if (!conn->file)
        die(conn, "Failed to open the file");

    return conn;
}

void Database_close(struct Connection *conn) {
    if (conn) {
        if (conn->file)
            fclose(conn->file);
        struct Database *db = conn->db;
        if (db) {
            if (db->rows) {
                for (int i = 0; i < db->max_rows; ++i) {
                    struct Address *addr = &db->rows[i];
                    if (addr->name) {
                        free(addr->name);
                    }
                    if (addr->email) {
                        free(addr->email);
                    }
                }
                free(db->rows);
            }
            free(db);
        }
        free(conn);
    }
}

void Database_write(struct Connection *conn) {
    FILE *file = conn->file;
    rewind(file);
    struct Database *db = conn->db;

    if (fwrite(&db->max_rows, sizeof(int), 1, file) != 1) {
        die(conn, "Fail to write database max_rows");
    }

    if (fwrite(&db->max_data, sizeof(int), 1, file) != 1) {
        die(conn, "Fail to write database max_data");
    }

    for (int i = 0; i < db->max_rows; ++i) {
        struct Address *addr = &db->rows[i];
        if (fwrite(&addr->id, sizeof(int), 1, file) != 1)
            die(conn, "Fail to write id");
        if (fwrite(&addr->set, sizeof(int), 1, file) != 1)
            die(conn, "Fail to write set");

        if (fwrite(addr->name, sizeof(char), db->max_data, file) !=
            db->max_data)
            die(conn, "Fail to write name");
        if (fwrite(addr->email, sizeof(char), db->max_data, file) !=
            db->max_data)
            die(conn, "Fail to write email");
    }
}

void Database_create(struct Connection *conn, int max_rows, int max_data) {
    conn->db->max_rows = max_rows;
    conn->db->max_data = max_data;
    conn->db->rows = malloc(sizeof(struct Address) * max_rows);
    for (int i = 0; i < max_rows; ++i) {
        struct Address addr = {.id = i, .set = 0};
        addr.name = calloc(max_data, sizeof(char));
        addr.email = calloc(max_data, sizeof(char));
        conn->db->rows[i] = addr;
    }
}

void Database_set(struct Connection *conn, int id, const char *name,
                  const char *email) {
    int max_data = conn->db->max_data;
    struct Address *addr = &conn->db->rows[id];

    if (addr->set)
        die(conn, "Already set, delete it first");

    addr->set = 1;

    char *res = strncpy(addr->name, name, max_data);
    addr->name[max_data - 1] = '\0';
    if (!res)
        die(conn, "Name copy failed");

    res = strncpy(addr->email, email, max_data);
    addr->email[max_data - 1] = '\0';
    if (!res)
        die(conn, "Email copy failed");
}

void Database_get(struct Connection *conn, int id) {
    struct Address *addr = &conn->db->rows[id];

    if (addr->set) {
        Address_print(addr);
    } else {
        die(conn, "ID is not set");
    }
}

void Database_delete(struct Connection *conn, int id) {
    struct Address *addr = &conn->db->rows[id];
    addr->set = 0;
}

void Database_list(struct Connection *conn) {
    struct Database *db = conn->db;
    int max_rows = db->max_rows;
    printf("Thers are %d rows of address\n", max_rows);
    for (int i = 0; i < max_rows; ++i) {
        struct Address *cur = &db->rows[i];
        if (cur->set) {
            Address_print(cur);
        }
    }
}

int main(int argc, char **argv) {
    if (argc < 3)
        die(NULL, "USAGE: ex17 <dbfile> <action> [action params]");

    char *filename = argv[1];
    char action = argv[2][0];
    struct Connection *conn = Database_open(filename, action);
    int id = 0;
    int max_data = conn->db->max_data;
    int max_rows = conn->db->max_rows;

    switch (action) {
    case 'c':
        if (argc != 5)
            die(conn, "Need max_rows, max_data to create");
        max_rows = atoi(argv[3]);
        max_data = atoi(argv[4]);
        Database_create(conn, max_rows, max_data);
        Database_write(conn);
        break;
    case 'g':
        if (argc != 4)
            die(conn, "Need an id to get");
        id = atoi(argv[3]);
        if (id >= max_rows || id < 0)
            die(conn, "There's not that name records");

        Database_get(conn, id);
        break;
    case 's':
        if (argc != 6)
            die(conn, "Need id, name, email to set");
        id = atoi(argv[3]);
        if (id >= max_rows || id < 0)
            die(conn, "There's not that name records");
        Database_set(conn, id, argv[4], argv[5]);
        Database_write(conn);
        break;
    case 'd':
        if (argc != 4)
            die(conn, "Need id to delete");
        id = atoi(argv[3]);
        if (id >= max_rows || id < 0)
            die(conn, "There's not that name records");
        Database_delete(conn, id);
        Database_write(conn);
        break;
    case 'l':
        Database_list(conn);
        break;
    default:
        die(conn, "Invalid action, "
                  "only:\n\tc=create\n\tg=get\n\ts=set\n\td=delete\n\tl=list");
    }

    Database_close(conn);

    return 0;
}
