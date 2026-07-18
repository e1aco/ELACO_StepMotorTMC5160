import sqlite3, json, sys

DB_PATH = r"C:\Users\electronic\.local\share\mimocode\mimocode.db"
conn = sqlite3.connect(DB_PATH)
conn.row_factory = sqlite3.Row
cur = conn.cursor()

# Find the project for this worktree
WORKTREE = r"E:\Desktop\XM\ELACO_StepMotorTMC5160\Firmware\StepMotorDriver_Keil"
cur.execute("SELECT * FROM project WHERE worktree LIKE ?", (f"%{WORKTREE}%",))
projects = cur.fetchall()
print("=== PROJECTS ===")
for p in projects:
    print(f"  id={p['id']}  name={p['name']}  worktree={p['worktree']}")

if not projects:
    # Try broader search
    cur.execute("SELECT * FROM project")
    all_proj = cur.fetchall()
    print("ALL projects:")
    for p in all_proj:
        print(f"  id={p['id']}  name={p['name']}  worktree={p['worktree']}")
    conn.close()
    sys.exit(0)

project_id = projects[0]['id']

# Sessions for this project
cur.execute("""
    SELECT s.id, s.title, s.time_created, s.directory,
           json_extract(s.data, '$.version') as version
    FROM session s
    WHERE s.project_id = ?
    ORDER BY s.time_created DESC
    LIMIT 20
""", (project_id,))
print(f"\n=== SESSIONS (project {project_id}) ===")
for s in cur.fetchall():
    import datetime
    ts = datetime.datetime.fromtimestamp(s['time_created'] / 1000).strftime('%Y-%m-%d %H:%M')
    print(f"  {s['id']}  [{ts}]  {s['title']}")

# Check messages count per session
print("\n=== MESSAGE COUNTS ===")
cur.execute("""
    SELECT s.id, s.title, COUNT(m.id) as msg_count
    FROM session s
    JOIN message m ON m.session_id = s.id
    WHERE s.project_id = ?
    GROUP BY s.id
    ORDER BY s.time_created DESC
    LIMIT 20
""", (project_id,))
for r in cur.fetchall():
    print(f"  {r['id']}  msgs={r['msg_count']}  {r['title']}")

conn.close()
