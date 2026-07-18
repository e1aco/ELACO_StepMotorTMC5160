import sqlite3, json, datetime

DB_PATH = r"C:\Users\electronic\.local\share\mimocode\mimocode.db"
conn = sqlite3.connect(DB_PATH)
conn.row_factory = sqlite3.Row
cur = conn.cursor()

# Focus on the 3 non-current sessions
sessions = [
    ("ses_0963545dbffeiXondJoOXDKzp0", "查看项目内容"),
    ("ses_09635be36ffeXz3SiCjA8GvDaI", "还记得代码规则吗"),
    ("ses_09635be86ffeHSsnmA0keX545E", "CAN RxFifo0 callback"),
]

for sid, title in sessions:
    print(f"\n{'='*80}")
    print(f"SESSION: {sid}  ({title})")
    print(f"{'='*80}")
    
    cur.execute("""
        SELECT m.id, m.agent_id, json_extract(m.data, '$.role') as role,
               m.time_created
        FROM message m
        WHERE m.session_id = ?
        ORDER BY m.time_created
    """, (sid,))
    messages = cur.fetchall()
    
    for msg in messages:
        ts = datetime.datetime.fromtimestamp(msg['time_created'] / 1000).strftime('%H:%M:%S')
        role = msg['role']
        agent = msg['agent_id'] or 'main'
        print(f"\n--- [{ts}] {role} (agent={agent}) msg_id={msg['id']} ---")
        
        # Get parts for this message
        cur.execute("""
            SELECT p.id, json_extract(p.data, '$.type') as part_type,
                   json_extract(p.data, '$.tool') as tool,
                   p.data
            FROM part p
            WHERE p.message_id = ?
            ORDER BY p.time_created
        """, (msg['id'],))
        parts = cur.fetchall()
        
        for p in parts:
            ptype = p['part_type']
            if ptype == 'text':
                d = json.loads(p['data'])
                text = d.get('text', '')
                # Truncate long text
                if len(text) > 500:
                    text = text[:500] + f"... [{len(d.get('text',''))} chars total]"
                print(f"  [text]: {text}")
            elif ptype == 'tool':
                d = json.loads(p['data'])
                tool_name = d.get('tool', 'unknown')
                state = d.get('state', {})
                inp = str(state.get('input', ''))[:200]
                out = str(state.get('output', ''))[:200]
                print(f"  [tool: {tool_name}] input={inp}")
                if out and out != 'None':
                    print(f"           output={out}")
            else:
                d = json.loads(p['data'])
                print(f"  [{ptype}]: {str(d)[:200]}")

conn.close()
