import pytesseract
from PIL import Image

image = Image.open("20180124211517874.png")
code = pytesseract.image_to_string(image,lang="chi_sim",config="-psm 6")
print(code)

