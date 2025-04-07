import mysql.connector
import requests

# 🔐 WPISZ TU SWOJE DANE LOGOWANIA DO BAZY
db_config = {
    'host': 'localhost',        # np. '127.0.0.1' lub adres zdalnego serwera
    'user': 'michal',
    'password': '1234',
    'database': 'bd_projekt'
}

# 1. Połączenie z MySQL
conn = mysql.connector.connect(**db_config)
cursor = conn.cursor()

# 2. Tworzenie tabeli jeśli nie istnieje
cursor.execute("""
CREATE TABLE IF NOT EXISTS users (
    id INT AUTO_INCREMENT PRIMARY KEY,
    username VARCHAR(255),
    email VARCHAR(255),
    hashed_password VARCHAR(255)
)
""")

# 3. Pobieranie danych z API
response = requests.get("https://randomuser.me/api/?results=100")
users = response.json()['results']

# 4. Wstawianie danych
for user in users:
    username = user['login']['username']
    email = user['email']
    password = user['login']['password']  # plaintext, dla testów OK

    cursor.execute("""
    INSERT INTO users (username, email, hashed_password)
    VALUES (%s, %s, %s)
    """, (username, email, password))

# 5. Zatwierdzenie zmian i zamknięcie połączenia
conn.commit()
cursor.close()
conn.close()

print("✅ Dodano 100 użytkowników do bazy danych!")
