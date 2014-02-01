#import MySQLdb
import serial
#from time import gmtime, strftime

#con = MySQLdb.connect('localhost', 'root', '') # conecta no servidor
#con.select_db('working_hours') # seleciona o banco de dados
#cursor = con.cursor()

ser = serial.Serial('/dev/ttyACM0', 9600)

while 1:
	#if ser.readline():
	ser.readline()
	print(ser.readline())
	#card_number = str(ser.readline())
       	#print(card_number)

	#sql = "insert into working_hours (card_number, created_at)  values('"+str(card_number)+"', '"+str(strftime("%Y-%m-%d %H:%M:%S", gmtime()))+"')"
	#cursor.execute(sql)
	#con.commit()

	ser.write('2')
