# 🔧 Flask Website: Data Structures Visualizer (AVL Tree & HashMap in C)

This project is a complete **Flask-based website** that demonstrates the implementation of **AVL Tree** and **HashMap** in **C**, with a simple and intuitive frontend using **HTML** and **CSS**. The backend is written in Python using Flask and interacts with a compiled C program (`dsa2.exe`).

---

## 🚀 Features

- 🌲 AVL Tree: Insert, Delete, and Traverse operations
- 🔑 HashMap: Insert, Search, and Delete operations
- 🖥️ Web-based interface using Flask
- 🔗 Python-C integration via `subprocess` or direct execution
- 🎓 Educational and practical for DSA learners

---

## 🛠️ Tech Stack

- **Frontend**: HTML, CSS (inside `templates.zip` and `static.zip`)
- **Backend**: Python with Flask (`server.py`)
- **Core Logic**: C (`dsa2.c` compiled as `dsa2.exe`)

---

## 📁 Project Structure

```
project-root/
│
├── README.md            # Project readme
├── dsa2.c               # C source file (AVL Tree and HashMap)
├── dsa2.exe             # Compiled C program
├── server.py            # Flask backend
├── static.zip           # CSS and static files (unzip to static/)
├── templates.zip        # HTML templates (unzip to templates/)
```

> 📦 Please unzip `static.zip` to a `static/` folder and `templates.zip` to a `templates/` folder before running.

---

## ▶️ How to Run

### 1. Unzip the required folders:

```bash
unzip templates.zip -d templates
unzip static.zip -d static
```

### 2. Install required Python libraries:

```bash
pip install flask
```

### 3. Run the Flask server:

```bash
python server.py
```

### 4. Open your browser and go to:

```
http://localhost:5000
```

---

## 🔧 How It Works

- User input is received via HTML forms in `templates/`
- Flask handles requests in `server.py`
- Backend executes the C binary (`dsa2.exe`) with required input
- Output from the C program is captured and returned to the user

---

## 🧠 Educational Purpose

This project demonstrates how:

- Low-level C code can be reused in high-level web applications
- Web interfaces can make learning DSA more interactive
- Python can integrate with compiled binaries (e.g., using `subprocess.run()`)

---

## 📸 Screenshots (optional)

| Home | AVL Tree | HashMap |
|------|----------|---------|
| *(Add screenshots here)* | *(Add AVL interface screenshot)* | *(Add HashMap interface screenshot)* |

---

## 📄 License

This project is provided for educational purposes. You may modify and use it as needed.

---

## 👤 Author

**Deekshith Gowda H. S**  
Reach out for collaboration or improvements!