# from flask import Flask, request, render_template, send_file
# import os
# import subprocess

# app = Flask(__name__)
# UPLOAD_FOLDER = 'uploads'
# os.makedirs(UPLOAD_FOLDER, exist_ok=True)

# @app.route('/')
# def index():
#     return render_template('index.html')

# @app.route('/compress', methods=['POST'])
# # def compress():
#     file = request.files['file']
#     filepath = os.path.join(UPLOAD_FOLDER, 'input.txt')
#     file.save(filepath)

#     # Run the Huffman C executable
#     subprocess.run(['backend/huffman'])

#     return send_file('backend/compressed.txt', as_attachment=True)

# if __name__ == '__main__':
#     app.run(debug=True)

from flask import Flask, request, render_template, send_file
import os
import subprocess

app = Flask(__name__)
UPLOAD_FOLDER = 'uploads'
os.makedirs(UPLOAD_FOLDER, exist_ok=True)

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/compress', methods=['POST'])
def compress():
    # Save uploaded file as input.txt in backend
    file = request.files['file']
    input_path = os.path.join('backend', 'input.txt')
    file.save(input_path)

    # Run the Huffman compression C program (creates compressed.bin)
    subprocess.run(['./backend/huffman'], shell=True)

    # Send compressed.bin file to user
    return send_file('backend/compressed.bin', as_attachment=True)

if __name__ == '__main__':
    app.run(debug=True)

