import MySQLdb
import serial
from time import gmtime, strftime

# con = MySQLdb.connect('localhost', 'root', '') # conecta no servidor
# con.select_db('working_hours') # seleciona o banco de dados
# cursor = con.cursor()

arduino = serial.Serial('/dev/ttyACM0', 9600)

# Cards to test
# Reynaldo = 942321812526
# Gui = 2069496193
# Rafael = 211191118134156
# JC = 243210116134211

while 1:
  card_number = arduino.readline().strip()
  print(card_number)

  #sql = "INSERT INTO working_hours (card_number, created_at)  VALUES ('"+str(card_number)+"', '"+str(strftime("%Y-%m-%d %H:%M:%S", gmtime()))+"')"
  #cursor.execute(sql)
  #con.commit()

  if card_number == "942321812526":
    arduino.write('1')
  elif card_number == "211191112134156":
    arduino.write('2')
  elif card_number == "243210116134211":
    arduino.write('3')
  elif card_number == "2069492193":
    arduino.write('4')
  elif card_number == "12345":
    arduino.write("Rafael\n")
