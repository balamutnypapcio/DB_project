# 🐬 MySQL + DataGrip — Szybki Start na Linuxie

Ten przewodnik pokaże Ci, jak:

1. Zainstalować MySQL na Linuxie  
2. Zabezpieczyć serwer  
3. Stworzyć użytkownika i bazę danych  
4. Połączyć się z bazą w **DataGrip**

---

## ✅ 1. Instalacja MySQL

```bash
sudo apt update
sudo apt install mysql-server
```

Sprawdź, czy usługa działa:

```bash
sudo systemctl status mysql
```

---

## 🔐 2. Konfiguracja zabezpieczeń

Uruchom skrypt zabezpieczający MySQL:

```bash
sudo mysql_secure_installation
```

**Zalecane odpowiedzi:**
- (opcjonalnie) Włącz walidację haseł
- Usuń anonimowych użytkowników → `y`
- Zablokuj zdalne logowanie root → `y`
- Usuń bazę testową → `y`
- Załaduj zmiany → `y`

---

## 🛠 3. Tworzenie użytkownika i bazy danych

### 🔑 Zaloguj się jako root:

```bash
sudo mysql -u root -p
```

### 👤 Utwórz użytkownika:

```sql
CREATE USER 'twoj_user'@'localhost' IDENTIFIED BY 'twoje_silne_haslo';
```

### 🛡 Nadaj uprawnienia:

```sql
GRANT ALL PRIVILEGES ON *.* TO 'twoj_user'@'localhost' WITH GRANT OPTION;
FLUSH PRIVILEGES;
```

### 🗃 (Opcjonalnie) Utwórz bazę danych:

```sql
CREATE DATABASE moja_baza;
```

### 🚪 Wyloguj się:

```sql
EXIT;
```

---

## 💻 4. Połączenie z MySQL w DataGrip

1. Otwórz **DataGrip**
2. Kliknij ➕ → **Data Source** → **MySQL**
3. Wypełnij dane:
   - **Host**: `localhost`
   - **Port**: `3306`
   - **User**: `twoj_user`
   - **Password**: `twoje_silne_haslo`
4. Kliknij **Test Connection**
5. Jeśli działa → **OK**

---

## ✅ 5. Gotowe!

Teraz możesz:
- Tworzyć tabele i relacje
- Wstawiać dane
- Pisać zapytania SQL
- Zarządzać bazami graficznie w **DataGrip** 🧠

---

## 🧠 FAQ

### ❓ Nie mogę się połączyć z DataGrip?
Sprawdź, czy MySQL działa i nasłuchuje:

```bash
sudo ss -tuln | grep 3306
```

### 🌐 Chcę pozwolić na zdalne połączenia
1. Edytuj plik konfiguracyjny:

```bash
sudo nano /etc/mysql/mysql.conf.d/mysqld.cnf
```

2. Zmień:

```
bind-address = 127.0.0.1
```

na:

```
bind-address = 0.0.0.0
```

3. Zrestartuj serwer:

```bash
sudo systemctl restart mysql
```

---

Jeśli coś nie działa — dopisz nowy punkt do tego README 😎
