import psycopg2

def initConnection(username = 'postgres',
                   password = 'root',
                   hostname = 'localhost',
                   port = '5432',
                   dbname = 'hospital'):
    try:
        conn = psycopg2.connect(
            host = hostname,
            port = port,
            dbname = dbname,
            user = username,
            password = password,
            client_encoding = 'utf-8',
            )

    except:
        pass

    conn.autocommit = True

    return conn

def runQuery(conn, query):
    with conn.cursor() as cursor:
        cursor.execute(query)
        data = cursor.fetchall()
        colnames = [desc[0] for desc in cursor.description]

        return (data, colnames)

def getAllTables(conn):
    with conn.cursor() as cursor:
        cursor.execute('SELECT table_name FROM information_schema.tables WHERE table_schema=\'public\'')
        data = cursor.fetchall()

        return data

def getTableData(conn, tableName):
    with conn.cursor() as cursor:
        cursor.execute(f'SELECT * FROM {tableName}')
        data = cursor.fetchall()
        colnames = [desc[0] for desc in cursor.description]
        
        return (data, colnames)

def addRecord(conn, tableName, keys, values):
    with conn.cursor() as cursor:
        try:
            cursor.execute(f'INSERT INTO {tableName} {keys} VALUES {values}')
            return None
        except:
            return "Убедитесь, что все поля заполнены правильно!"

def deleteRecord(conn, tableName, parameters):
    with conn.cursor() as cursor:
        try:
            cursor.execute(f'DELETE FROM {tableName} WHERE {parameters}')
            return None
        except:
            return "На данную запись существуют ссылки в других таблицах!"
        
def updateRecord(conn, tableName, setString, parameters):
    with conn.cursor() as cursor:
        try:
            cursor.execute(f'UPDATE {tableName} SET {setString} WHERE {parameters}')
            return None
        except:
            return "Убедитесь, что все поля заполнены правильно!"
      
def getButtonInfo():
    return (
        ['Вывести ФИО и номер истории болезни пацентов', 
         'SELECT history_number, first_name, middle_name, surname FROM patient'],
        ['Вывести название анализа и дату его взятия', 
         'SELECT test_name, date_ FROM test'],
        ['Вывести фамилии врачей с высшей квалификацией',
         'SELECT surname, qualification FROM doctor WHERE qualification LIKE \'Higher\''],
        ['Вывести все услуги, цена для граждан Беларуси на которые больше 70',
         'SELECT * FROM service WHERE price_for_belarusian > 70'],
        ['Вывести отделения с кол-вом койко-мест больше 25 и отсортировать по возрастанию',
         'SELECT * FROM department WHERE number_of_beds > 25 ORDER BY number_of_beds ASC'],
        ['Вывести 10 последних выставленных дигнозов и отсортировать по убыванию',
         'SELECT * FROM diagnosis ORDER BY date_ DESC LIMIT 10'],
        ['Вывести информацию о пациентах, которым проводилось МРТ с дополнительной информацией о дате исследования',
         'SELECT patient.history_number, type_of_treatment, surname, first_name, middle_name, department_name, test_name, date_ FROM patient CROSS JOIN test WHERE patient.history_number = test.history_number AND test_name LIKE \'MRI\''],
        ['Вывести информацию о пациентах, которым диагнозы были выставлены в октябре 2023 года с дополнительной информацией о названии диагноза',
         'SELECT patient.history_number, type_of_treatment, surname, first_name, middle_name, department_name, diagnosis_name, date_ FROM patient CROSS JOIN diagnosis WHERE patient.history_number = diagnosis.history_number AND date_ >= \'2023-10-01\' AND date_ <= \'2023-10-31\''],
        ['Вывести фамилии врачей, которые предоставляют услугу "Удаление татуировки", и их квалификацию',
         'SELECT doctor.doctor_id, surname, qualification, service_name FROM doctor INNER JOIN doctor_service ON (doctor.doctor_id = doctor_service.doctor_id) AND service_name LIKE \'Tattoo Removal\''],
        ['Вывести информацию о пациентах, которые лежат в отделениях, где меньше 25 койко-мест',
         'SELECT history_number, surname, type_of_treatment, patient.department_name, number_of_beds FROM patient INNER JOIN department ON (patient.department_name = department.department_name) WHERE number_of_beds < 25'],
        ['Вывести информацию о пациентах, которым предоставлена консультация и поставлен диагноз (LEFT OUTER JOIN)',
         'SELECT patient.history_number, surname, type_of_treatment, department_name, diagnosis_name FROM patient LEFT OUTER JOIN diagnosis ON (patient.history_number = diagnosis.history_number) WHERE type_of_treatment LIKE \'Consultation\''],
        ['Вывести информацию о врачах и платных услугах, которые эти врачи предоставляют (LEFT OUTER JOIN)',
         'SELECT doctor.doctor_id, surname, qualification, service_name FROM doctor LEFT OUTER JOIN doctor_service ON (doctor.doctor_id = doctor_service.doctor_id)'],
        ['Вывести информацию о пациентах, которым предоставлена консультация и поставлен диагноз (RIGHT OUTER JOIN)',
         'SELECT * FROM diagnosis RIGHT OUTER JOIN patient ON (diagnosis.history_number = patient.history_number) WHERE type_of_treatment LIKE \'Consultation\''],
        ['Вывести информацию о врачах с высшей квалификацией и платных услугах, которые эти врачи предоставляют (RIGHT OUTER JOIN)',
         'SELECT * FROM doctor_service RIGHT OUTER JOIN doctor ON (doctor_service.doctor_id = doctor.doctor_id) WHERE qualification LIKE \'Higher\''],
        ['Вывести список пациентов с дополнительной информацией об осмотре пациента врачом в период с 01.01.2023 по 15.01.2023',
         'SELECT * FROM patient FULL OUTER JOIN doctor_patient ON (patient.history_number = doctor_patient.history_number) WHERE date_ >= \'2023-01-01\' AND date_ <= \'2023-01-15\''],
        ['Вывести список пациентов, которым были выставлены последние 10 диагнозов с дополнительной информацией о диагнозе',
         'SELECT * FROM patient FULL OUTER JOIN diagnosis ON (patient.history_number = diagnosis.history_number) WHERE diagnosis_id IS NOT NULL ORDER BY date_ DESC LIMIT 10'],
        ['Вывести информации об общей стоимости услуг для граждан Беларуси, предоставляемых врачами с высшей категорией',
         'SELECT SUM(price_for_belarusian) AS total_price FROM doctor INNER JOIN doctor_service ON (doctor.doctor_id = doctor_service.doctor_id) INNER JOIN service ON (doctor_service.service_name = service.service_name) WHERE qualification LIKE \'Higher\''],
        ['Вывести среднюю стоимость платных услуг для иностранных граждан',
         'SELECT AVG(price_for_foreigners) AS average_price FROM service'],
        ['Вывести кол-во анализов крови, выполненных в период с \'01.01.2024\' по \'20.01.2024\'',
         'SELECT COUNT(test_name) AS count_ FROM test WHERE test_name LIKE \'Blood Test\' AND date_ >= \'2024-01-01\' AND date_ <= \'2024-01-20\''],
        ['Вывести информацию об отделениях с наименьшим кол-вом койко-мест',
         'SELECT * FROM department WHERE number_of_beds = (SELECT MIN(number_of_beds) FROM department)'],
        ['Вывести информацию об отделениях с наибольшим кол-вом койко-мест',
         'SELECT * FROM department WHERE number_of_beds = (SELECT MAX(number_of_beds) FROM department)'],
        ['Вывести информацию о количестве того, сколько раз был выполнен каждый из возможных анализов',
         'SELECT test_name, COUNT(*) AS number_ FROM test GROUP BY test_name'],
        ['Вывести информацию о кол-ве врачей каждой из категорий, при том, что кол-во врачей в каждой из выведенных категорий должно быть больше 5',
         'SELECT COUNT(doctor_id), qualification FROM doctor GROUP BY qualification HAVING COUNT(doctor_id) > 5'],
        ['Вывести пациентов, относящихся к отделениям кардиологии и педиатрии',
         'SELECT patient.history_number, patient.surname, patient.department_name FROM patient WHERE department_name IN (\'Cardiology\', \'Pediatrics\')'],
        ['Вывести информацию об анализах, сделанных лаборантами с фамилией Johnson',
         'SELECT * FROM test WHERE name_of_nurse = ANY (SELECT name_of_nurse FROM test WHERE name_of_nurse LIKE \'Johnson\')'],
        ['Вывести информацию об анализах, взятых у пацентов, чья история болезни имеет номер больше 1020',
         'SELECT * FROM test WHERE history_number <> ALL (SELECT history_number FROM test WHERE history_number < 1020)'],
        ['Вывести информацию о врачах, которые являются главными врачами отделений',
         'SELECT surname, speciality FROM doctor WHERE EXISTS (SELECT surname_of_head FROM department WHERE department.surname_of_head = doctor.surname)'],
        ['Вывести врачей, которые имеют вторую категорию, или проводят анализ крови, или осматривали пациентов 01.01.2024 (без повторений)',
         'SELECT doctor_id FROM doctor WHERE qualification LIKE \'Second\' UNION SELECT doctor_id FROM doctor_service WHERE service_name LIKE \'Blood Test\' UNION SELECT doctor_id FROM doctor_patient WHERE date_ = \'2024-01-01\''],
        ['Вывести врачей, которые имеют вторую категорию, или проводят анализ крови, или осматривали пациентов 01.01.2024 (с повторениями)',
         'SELECT doctor_id FROM doctor WHERE qualification LIKE \'Second\' UNION ALL SELECT doctor_id FROM doctor_service WHERE service_name LIKE \'Blood Test\' UNION ALL SELECT doctor_id FROM doctor_patient WHERE date_ = \'2024-01-01\''],
        ['Вывести врачей, которые имеют высшую категорию, выполняют удаление татуировок и проводили осмотр пациента 28.01.2023',
         'SELECT doctor_id FROM doctor WHERE qualification LIKE \'Higher\' INTERSECT SELECT doctor_id FROM doctor_service WHERE service_name LIKE \'Tattoo Removal\' INTERSECT SELECT doctor_id FROM doctor_patient WHERE date_ > \'2023-01-01\''],
        ['Вывести номер истории болезни пациентов, которым делали анализ крови, которые не обращались за консультацией, и которых не осматривали после 15.01.2023',
         'SELECT history_number FROM test WHERE test_name LIKE \'Blood Test\' EXCEPT SELECT history_number FROM patient WHERE type_of_treatment LIKE \'Consultation\' EXCEPT SELECT history_number FROM doctor_patient WHERE date_ > \'2023-01-15\'']
    )