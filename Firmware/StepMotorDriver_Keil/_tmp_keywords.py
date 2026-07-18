import sqlite3, json, datetime

DB_PATH = r"C:\Users\electronic\.local\share\mimocode\mimocode.db"
conn = sqlite3.connect(DB_PATH)
conn.row_factory = sqlite3.Row
cur = conn.cursor()

PROJECT_ID = "3c320fb6-60ca-45ed-a576-ca2ada58d809"

# Search user messages for rule/decision keywords
keywords = ["记住", "规则", "以后", "always", "never", "remember", "rule", "规范", "存到", "项目里面"]

for kw in keywords:
    cur.execute("""
        SELECT m.id, m.session_id, m.time_created,
               json_extract(m.data, '$.role') as role
        FROM message m
        JOIN part p ON p.message_id = m.id
        WHERE m.session_id IN (
            SELECT id FROM session WHERE project_id = ?
        )
        AND json_extract(m.data, '$.role') = 'user'
        AND p.data LIKE ?
        ORDER BY m.time_created
        LIMIT 5
    """, (PROJECT_ID, f"%{kw}%"))
    rows = cur.fetchall()
    if rows:
        print(f"\n=== Keyword: '{kw}' ===")
        for r in rows:
            ts = datetime.datetime.fromtimestamp(r['time_created'] / 1000).strftime('%Y-%m-%d %H:%M')
            # Get the text content
            cur2 = conn.cursor()
            cur2.execute("""
                SELECT json_extract(p.data, '$.text') as text
                FROM part p
                WHERE p.message_id = ?
                AND json_extract(p.data, '$.type') = 'text'
            """, (r['id'],))
            text_row = cur2.fetchone()
            text = text_row['text'][:200] if text_row else "(no text)"
            print(f"  [{ts}] ses={r['session_id']}: {text}")

# Also search for user statements about parameter groups and motor count
for kw in ["参数组", "5个电机", "两个电机", "芯片1", "U1", "占位", "暂时定"]:
    cur.execute("""
        SELECT m.id, m.session_id, m.time_created,
               json_extract(m.data, '$.role') as role
        FROM message m
        JOIN part p ON p.message_id = m.id
        WHERE m.session_id IN (
            SELECT id FROM session WHERE project_id = ?
        )
        AND json_extract(m.data, '$.role') = 'user'
        AND p.data LIKE ?
        ORDER BY m.time_created
        LIMIT 3
    """, (PROJECT_ID, f"%{kw}%"))
    rows = cur.fetchall()
    if rows:
        print(f"\n=== Keyword: '{kw}' ===")
        for r in rows:
            ts = datetime.datetime.fromtimestamp(r['time_created'] / 1000).strftime('%Y-%m-%d %H:%M')
            cur2 = conn.cursor()
            cur2.execute("""
                SELECT json_extract(p.data, '$.text') as text
                FROM part p
                WHERE p.message_id = ?
                AND json_extract(p.data, '$.type') = 'text'
            """, (r['id'],))
            text_row = cur2.fetchone()
            text = text_row['text'][:300] if text_row else "(no text)"
            print(f"  [{ts}] ses={r['session_id']}: {text}")

conn.close()
