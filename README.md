# 🔧 Flask Website: Data Structures Visualizer (AVL Tree & HashMap in C)

This is a fully functional **Flask-based website** with an interactive frontend built using **HTML, CSS, and Bootstrap**, which integrates the implementation of two essential data structures — **AVL Tree** and **HashMap**, both written in **C** and connected via the backend.

---

## 🚀 Features

- 🌲 **AVL Tree** Implementation: Insertion, deletion, and traversal
- 🔑 **HashMap** Implementation: Insert, search, delete operations
- 🌐 Full stack integration: HTML/CSS frontend, Flask backend, C logic using Python-C bindings
- 📈 Visual feedback on operations performed on the data structures
- 💡 Educational: Designed to help understand how these data structures work under the hood

---

## 🛠️ Tech Stack

- **Frontend**: HTML, CSS, Bootstrap
- **Backend**: Python (Flask)
- **Core Logic**: C (AVL Tree & HashMap implementation)
- **Integration**: Python `ctypes` or `cffi` for calling C functions from Flask

---

## 📂 Folder Structure

```
project-root/
│
├── static/               # CSS files and static assets
│   └── style.css
│
├── templates/            # HTML templates
│   ├── index.html
│   └── avl.html
│   └── hashmap.html
│
├── c_code/               # C implementations
│   ├── avl.c
│   ├── avl.h
│   ├── hashmap.c
│   ├── hashmap.h
│   └── Makefile
│
├── app.py                # Main Flask application
├── README.md             # Project README
└── requirements.txt      # Python dependencies
```

---

## 🔄 How to Run the Project

### 📥 1. Clone the Repository

```bash
git clone https://github.com/yourusername/flask-avl-hashmap-visualizer.git
cd flask-avl-hashmap-visualizer
```

### 🧰 2. Install Python Dependencies

```bash
pip install -r requirements.txt
```

### ⚙️ 3. Compile the C Code

```bash
cd c_code
make
cd ..
```

> This generates shared libraries (e.g., `.so` files) that Flask can call.

### ▶️ 4. Run the Flask Server

```bash
python app.py
```

### 🌐 5. Access the Website

Open your browser and navigate to:

```
http://localhost:5000
```

---

## 🔍 Implementation Overview

### ✅ AVL Tree (in C)
- Self-balancing binary search tree
- Implemented with:
  - Rotation logic (LL, RR, LR, RL)
  - Node insertion and deletion
  - Height and balance factor tracking

### ✅ HashMap (in C)
- Uses separate chaining with linked lists
- Implements:
  - Hash function for string/integer keys
  - Insert, search, and delete operations
  - Dynamic resizing optional

---

## 📸 Screenshots (Add your screenshots here)

| Homepage | AVL Tree | HashMap |
|----------|----------|---------|
| ![home](screenshots/home.png) | ![avl](screenshots/avl.png) | ![hash](screenshots/hashmap.png) |

---

## 🧠 Educational Use

This project is designed for learning purposes to:

- Visualize how data structures behave
- Understand Python <--> C integration
- Build full stack apps with low-level computation

---

## 📄 License

This project is licensed under the MIT License.

---

## 👨‍💻 Author

**Deekshith Gowda H. S**  
Feel free to connect or contribute!