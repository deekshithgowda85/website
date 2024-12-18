from flask import Flask, render_template_string, request,render_template
import subprocess
app = Flask(__name__)

# Dummy data storage (in memory)
records = {}

# HTML content (template with embedded CSS)
html_template = """
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/6.5.2/css/all.min.css">

    <title>DSA Project</title>
    <style>
@import url('https://fonts.googleapis.com/css2?family=Poppins:wght@100;200;300;400;500;600&display=swap');

* {
    margin: 0;
    padding: 0;
    box-sizing: border-box;
    text-decoration: none;
    border: none;
    outline: none;
    font-family: 'Poppins', sans-serif;
}
html{
    font-size: 62.5%;
}
body{
    width: 100%;
    height: 100vh;
    overflow-x: hidden;
    background-color: black;
    color: white;
  

}

header {
 position: fixed;
    margin-top: 20px;
    position: fixed;
    top: 0;
    left: 0;
    width: 100%;
    padding: 1rem 9%;
    background-color: transparent;
    display: flex;
    justify-content: space-between;
    align-items: center;
    z-index: 1000;
}

.logo {
    font-size: 3rem;
    color: #b74b4b;
    font-weight: 800;
    cursor: pointer;
    transition: 0.5s ease;
}

.logo:hover {
    transform: scale(1.1);
}

nav a {
    font-size: 1.8rem;
    color: white;
    margin-left: 4rem;
    font-weight: 500;
    transition: 0.3s ease;
    border-bottom: 3px solid transparent;
}

nav a:hover,
nav a.active {
    color: #b74b4b;
    border-bottom: 3px solid #b74b4b;
}

@media (max-width: 995px) {
    nav {
        position: absolute;
        display: none;
        top: 0;
        right: 0;
        width: 40%;
        border-left: 3px solid #b74b4b;
        border-bottom: 3px solid #b74b4b;
        border-bottom-left-radius: 2rem;
        padding: 1rem solid;
        background-color: #161616;
    }

    nav.active {
        display: block;
    }

    nav a {
        display: block;
        font-size: 2rem;
        margin: 3rem 0;
    }

    nav a:hover, nav a.active {
        padding: 1rem;
        border-radius: 0.5rem;
        border-bottom: 0.5rem solid #b74b4b;
    }
}

        body {
            margin: 0;
            padding: 2rem;
            font-family: Arial, sans-serif;
            background-color: #0d0d0d;
            color: white;
        }

        /* Division Layout */
        .container {
          display: grid;
          grid-template-columns: repeat(2, 1fr);  
          grid-template-rows: repeat(auto-fill, minmax(100px, 1fr));  
          gap: 2rem;
          margin: 2rem;
        }

        .division {
            border: 2px solid #b74b4b;
            border-radius: 1rem;
            background-color: #000000;
            padding: 2rem;
            display: flex;
            flex-direction: column;
            gap: 1rem;
        }

        .division h2 {
            font-size: 2rem;
            color: #b74b4b;
            text-align: center;
        }

        .division form {
            display: flex;
            flex-direction: column;
            gap: 1rem;
        }

        .division input, .division button {
            padding: 1rem;
            border: 1px solid #b74b4b;
            border-radius: 0.5rem;
            background-color: #161616;
            color: white;
            font-size: 1.2rem;
        }

        .division button {
            display: inline-block;
            padding: 1rem 2.8rem;
            background-color: black;
            border-radius: 4rem;
            font-size: 1.6rem;
            color: #b74b4b;
            letter-spacing: 0.3rem;
            font-weight: 600;
            border: 2px solid #b74b4b;
            transition: 0.3s ease;
            cursor: pointer;
        }

        .division button:hover {
            transform: scale3d(1.03);
            background-color: #b74b4b;
            color: black;
            box-shadow: 0 0 25px #b74b4b;
        }

        /* Output Terminal */
        #output-terminal {
            grid-column: span 2;
            margin-top: 2rem;
            padding: 2rem;
            border: 2px solid #b74b4b;
            border-radius: 1rem;
            background-color: #000000;
            color: white;
            font-size: 1.2rem;
        }
    </style>
</head>
<body>
    <header>
        <a href="{{ url_for('source') }}" class="logo">AVL TREE AND HASHMAP</a>
        <nav>    
    <a href="{{ url_for('website') }}">Home</a>
    <a href="{{ url_for('home') }}">Code</a>
    <a href="/" class="active">Implementation</a>
    <a href="{{ url_for('about') }}">About us</a>
    </header>
    <section class="Implementation">
        <br><br><br>
        <h1 style="text-align: center; color: #b74b4b; font-size: 5rem;">Database System</h1>

        <div class="container">
            <!-- Insert Record Division -->
            <div class="division">
                <h2>Insert Record</h2>
                <form id="insertForm" action="/insert" method="post">
                    <input type="hidden" name="operation" value="insert">
                    <input type="text" name="primaryKey" placeholder="Enter Primary Key" required>
                    <input type="text" name="secondaryKey" placeholder="Enter Secondary Key" required>
                    <input type="text" name="data" placeholder="Enter Data" required>
                    <button type="submit">Submit</button>
                </form>
            </div>

            <!-- Search by Primary Key Division -->
            <div class="division">
                <h2>Search by Primary Key</h2>
                <form id="searchForm" action="/search" method="post">
                    <input type="hidden" name="operation" value="search">
                    <input type="text" name="primaryKey" placeholder="Enter Primary Key" required>
                    <button type="submit">Search</button>
                </form>
            </div>

            <!-- Search by Range Division -->
            <div class="division">
                <h2>Search by Range</h2>
                <form id="rangeForm" action="/range-query" method="post">
                    <input type="hidden" name="operation" value="range">
                    <input type="text" name="rangeStart" placeholder="Enter From Secondary Key" required>
                    <input type="text" name="rangeEnd" placeholder="Enter To Secondary Key" required>
                    <button type="submit">Search Range</button>
                </form>
            </div>

            <!-- View Cache Division -->
            <div class="division">
                <h2>View Cache</h2>
                <button id="viewCacheButton" onclick="window.location.href='/view-cache';">View Cache</button>
            </div>
       

<!-- Delete Record Division -->
<div class="division">
    <h2>Delete Record</h2>
    <form id="deleteForm" action="/delete" method="post">
        <input type="hidden" name="operation" value="delete">
        <input type="text" name="primaryKey" placeholder="Enter Primary Key" required>
        <button type="submit">Delete</button>
    </form>
</div>


<!-- View All Records Division -->
<div class="division">
    <h2>View All Records</h2>
    <button id="viewAllButton" onclick="window.location.href='/view-all';">View All Records</button>
</div>
 </div>
        <!-- Output Terminal -->
        <div id="output-terminal">
            <h2>Output Terminal</h2>
            <p id="output">{{ output }}</p>
        </div>
    </section>
</body>
</html>
"""

@app.route('/')
def index():
    return render_template_string(html_template, output="Welcome to the Database System")

@app.route('/insert', methods=['POST'])
def insert_record():
    primary_key = request.form['primaryKey']
    secondary_key = request.form['secondaryKey']
    data = request.form['data']
    records[primary_key] = {'secondary_key': secondary_key, 'data': data}
    message = f"Record Inserted: Primary Key - {primary_key}, Secondary Key - {secondary_key}, Data - {data}"
    return render_template_string(html_template, output=message)

@app.route('/search', methods=['POST'])
def search_primary():
    primary_key = request.form['primaryKey']
    record = records.get(primary_key, None)
    if record:
        message = f"Found record with Primary Key: {primary_key}, Secondary Key: {record['secondary_key']}, Data: {record['data']}"
    else:
        message = f"No record found for Primary Key: {primary_key}"
    return render_template_string(html_template, output=message)

@app.route('/range-query', methods=['POST'])
def search_range():
    range_start = request.form['rangeStart']
    range_end = request.form['rangeEnd']
    range_result = {k: v for k, v in records.items() if range_start <= v['secondary_key'] <= range_end}
    if range_result:
        result_str = "\n".join([f"Primary Key: {k}, Secondary Key: {v['secondary_key']}, Data: {v['data']}" for k, v in range_result.items()])
        message = f"Found records in the range {range_start} to {range_end}:\n{result_str}"
    else:
        message = f"No records found in the range {range_start} to {range_end}."
    return render_template_string(html_template, output=message)

@app.route('/view-cache', methods=['GET'])
def view_cache():
    if records:
        result_str = "\n".join([f"Primary Key: {k}, Secondary Key: {v['secondary_key']}, Data: {v['data']}" for k, v in records.items()])
        message = f"Cache Contents:\n{result_str}"
    else:
        message = "No records in cache."
    return render_template_string(html_template, output=message)

@app.route('/delete', methods=['POST'])
def delete():
    primary_key = request.form['primaryKey']

    if not primary_key:
        return render_template(html_template, output="Primary Key is required to delete!")

    if primary_key in records:
        del records[primary_key]
        message = "Record deleted successfully."
    else:
        message = f"No record found for Primary Key: {primary_key}"
    return render_template_string(html_template, output=message)

@app.route('/view-all', methods=['GET'])
def view_all():
    if records:
        result_str = "\n".join([f"Primary Key: {k}, Secondary Key: {v['secondary_key']}, Data: {v['data']}" for k, v in records.items()])
        output = f"All Records:\n{result_str}"
    else:
        output = "No records available."
    return render_template_string(html_template, output=output)




@app.route('/website')
def website():
    return render_template('website.html')

@app.route('/home')
def home():
    return render_template('home.html')

@app.route('/about')
def about():
    return render_template('about.html')

@app.route('/source')
def source():
    return render_template('source.html')

@app.route('/')
def url():
    return redirect('')

@app.route('/run_dsa')
def run_dsa():
    try:
        # Run the executable
        subprocess.run(['dsa2.exe'], check=True)
        return jsonify({"status": "success", "message": "dsa.exe executed successfully."})
    except subprocess.CalledProcessError as e:
        return jsonify({"status": "error", "message": f"Failed to execute dsa.exe: {e}"})

    
if __name__ == '__main__':
    app.run(debug=True)

