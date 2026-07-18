import sqlite3, json, sys

DB_PATH = r"C:\Users\electronic\.local\share\mimocode\mimocode.db"
conn = sqlite3.connect(DB_PATH)
conn.row_factory = sqlite3.Row
cur = conn.cursor()

print("=== TABLES ===")
cur.execute("SELECT name FROM sqlite_master WHERE type='table'")
for r in cur.fetchall():
    print(r[0])

print("\n=== SCHEMA ===")
cur.execute("SELECT name, sql FROM sqlite_master WHERE type='table'")
for r in cur.fetchall():
    print(f"\n--- {r[0]} ---")
    print(r[1])

conn.close()
