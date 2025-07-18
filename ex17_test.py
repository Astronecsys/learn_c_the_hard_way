import subprocess
import os
import pytest
import tempfile

EX17_BIN = "./ex17"

def run_cmd(args):
    proc = subprocess.run(
        [EX17_BIN] + args,
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
        text=True
    )
    return proc.stdout, proc.stderr, proc.returncode

@pytest.fixture(scope="module", autouse=True)
def check_ex17_bin():
    if not os.path.isfile(EX17_BIN) or not os.access(EX17_BIN, os.X_OK):
        pytest.skip("ex17 binary not found or not executable")

@pytest.fixture
def db_file():
    with tempfile.NamedTemporaryFile(delete=True) as tf:
        yield tf.name

def test_create(db_file):
    out, err, code = run_cmd([db_file, 'c', '5', '64'])
    assert code == 0
    assert err == ""

def test_set_and_get(db_file):
    # 先创建数据库
    run_cmd([db_file, 'c', '5', '64'])
    
    # 设置 id=1 的记录
    out, err, code = run_cmd([db_file, 's', '1', 'Alice', 'alice@example.com'])
    assert code == 0
    assert err == ""
    
    # 获取 id=1 记录，检查输出包含 Alice 和邮箱
    out, err, code = run_cmd([db_file, 'g', '1'])
    assert code == 0
    assert "Alice" in out
    assert "alice@example.com" in out

def test_get_unset_id(db_file):
    run_cmd([db_file, 'c', '5', '64'])
    # 试图 get 一个没设置的 id，应失败
    out, err, code = run_cmd([db_file, 'g', '3'])
    assert code != 0
    assert "ID is not set" in out or "ID is not set" in err

def test_delete(db_file):
    run_cmd([db_file, 'c', '5', '64'])
    run_cmd([db_file, 's', '2', 'Bob', 'bob@example.com'])
    
    # 删除 id=2
    out, err, code = run_cmd([db_file, 'd', '2'])
    assert code == 0
    
    # 再 get id=2 应该失败
    out, err, code = run_cmd([db_file, 'g', '2'])
    assert code != 0
    assert "ID is not set" in out or "ID is not set" in err

def test_list(db_file):
    run_cmd([db_file, 'c', '5', '64'])
    run_cmd([db_file, 's', '0', 'Alice', 'alice@example.com'])
    run_cmd([db_file, 's', '1', 'Bob', 'bob@example.com'])
    
    out, err, code = run_cmd([db_file, 'l'])
    assert code == 0
    assert "Alice" in out
    assert "Bob" in out

def test_set_existing(db_file):
    run_cmd([db_file, 'c', '5', '64'])
    run_cmd([db_file, 's', '0', 'Alice', 'alice@example.com'])
    
    # 再次设置同一个 id 应该失败
    out, err, code = run_cmd([db_file, 's', '0', 'Alice2', 'alice2@example.com'])
    assert code != 0
    assert "Already set, delete it first" in out or "Already set, delete it first" in err

def test_invalid_action(db_file):
    run_cmd([db_file, 'c', '5', '64'])
    out, err, code = run_cmd([db_file, 'x'])
    assert code != 0
    assert "Invalid action" in out or "Invalid action" in err   
    
def test_find(db_file):
    # 先创建数据库
    run_cmd([db_file, 'c', '5', '64'])
    
    # 插入两条记录
    run_cmd([db_file, 's', '0', 'Alice', 'alice@example.com'])
    run_cmd([db_file, 's', '1', 'Bob', 'bob@example.com'])
    
    # 查找 Alice
    out, err, code = run_cmd([db_file, 'f', 'Alice'])
    assert code == 0
    assert "Alice" in out
    assert "alice@example.com" in out
    
    # 查找 Bob
    out, err, code = run_cmd([db_file, 'f', 'Bob'])
    assert code == 0
    assert "Bob" in out
    assert "bob@example.com" in out
    
    # 查找不存在的 Charlie
    out, err, code = run_cmd([db_file, 'f', 'Charlie'])
    assert code == 0  # 注意：你的实现即使找不到也不会报错，只会打印 Empty Address
    assert "Empty Address" in out
