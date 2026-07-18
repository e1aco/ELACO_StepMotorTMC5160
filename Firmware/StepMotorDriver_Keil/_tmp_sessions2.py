import sqlite3, json, datetime

DB_PATH = r"C:\Users\electronic\.local\share\mimocode\mimocode.db"
conn = sqlite3.connect(DB_PATH)
conn.row_factory = sqlite3.Row
cur = conn.cursor()

PROJECT_ID = "3c320fb6-60ca-45ed-a576-ca2ada58d809"
OLD_PROJECT_ID = "1dedd77e-1d4e-434b-8378-a324e4316793"

for pid, label in [(PROJECT_ID, "CURRENT"), (OLD_PROJECT_ID, "OLD")]:
    cur.execute("""
        SELECT s.id, s.title, s.time_created, s.directory
        FROM session s
        WHERE s.project_id = ?
        ORDER BY s.time_created DESC
        LIMIT 20
    """, (pid,))
    sessions = cur.fetchall()
    print(f"\n=== SESSIONS ({label} project: {pid}) ===")
    for s in sessions:
        ts = datetime.datetime.fromtimestamp(s['time_created'] / 1000).strftime('%Y-%m-%d %H:%M')
        print(f"  {s['id']}  [{ts}]  {s['title']}")

    print(f"\n=== MESSAGE COUNTS ({label}) ===")
    cur.execute("""
        SELECT s.id, s.title, s.time_created, COUNT(m.id) as msg_count
        FROM session s
        JOIN message m ON m.session_id = s.id
        WHERE s.project_id = ?
        GROUP BY s.id
        ORDER BY s.time_created DESC
        LIMIT 20
    """, (pid,))
    for r in cur.fetchall():
        ts = datetime.datetime.fromtimestamp(r['time_created'] / 1000).strftime('%Y-%m-%d %H:%M')
        print(f"  {r['id']}  [{ts}]  msgs={r['msg_count']}  {r['title']}")

conn.close()
