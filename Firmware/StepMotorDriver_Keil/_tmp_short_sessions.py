import sqlite3, json, datetime

DB_PATH = r"C:\Users\electronic\.local\share\mimocode\mimocode.db"
conn = sqlite3.connect(DB_PATH)
conn.row_factory = sqlite3.Row
cur = conn.cursor()

# Short sessions
for SID in ["ses_0963545dbffeiXondJoOXDKzp0", "ses_09635bbebffeEbYCwg450O3L2f"]:
    cur.execute("""
        SELECT m.id, m.agent_id, json_extract(m.data, '$.role') as role,
               m.time_created
        FROM message m
        WHERE m.session_id = ?
        ORDER BY m.time_created
    """, (SID,))
    messages = cur.fetchall()
    
    cur.execute("SELECT title FROM session WHERE id = ?", (SID,))
    title_row = cur.fetchone()
    title = title_row['title'] if title_row else "unknown"
    
    print(f"\n{'='*80}")
    print(f"SESSION: {SID}  title={title}  msgs={len(messages)}")
    print(f"{'='*80}")
    
    for msg in messages:
        ts = datetime.datetime.fromtimestamp(msg['time_created'] / 1000).strftime('%H:%M:%S')
        role = msg['role']
        agent = msg['agent_id'] or 'main'
        
        cur.execute("""
            SELECT json_extract(p.data, '$.type') as part_type,
                   json_extract(p.data, '$.text') as text,
                   json_extract(p.data, '$.tool') as tool,
                   p.data
            FROM part p
            WHERE p.message_id = ?
            ORDER BY p.time_created
        """, (msg['id'],))
        parts = cur.fetchall()
        
        texts = []
        for p in parts:
            if p['part_type'] == 'text':
                t = p['text'] or ''
                if t:
                    texts.append(t[:400])
            elif p['part_type'] == 'tool':
                d = json.loads(p['data'])
                tool = d.get('tool', '?')
                out = str(d.get('state', {}).get('output', ''))[:200]
                texts.append(f"[tool:{tool}] {out}")
        
        if texts:
            combined = ' | '.join(texts)[:500]
            print(f"  [{ts}] {role}: {combined}")

conn.close()
