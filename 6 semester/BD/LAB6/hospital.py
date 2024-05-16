from database import *
import tkinter as tk
from tkinter import ttk
from tkinter import messagebox

def initWindow():
    root = tk.Tk()

    root.title('Hospital')
    root.geometry("900x587+100+80")
    root.resizable(False, False)
    root.configure(background='#FCCBE0')

    newTable = addTable(root)
    selectedTable = addTableChoice(root)
    CRUDButtons = addCRUDButtons(root)
    

    addQueryChoice(root)

    return (root, newTable, CRUDButtons, selectedTable)

def addTable(parent):
    def onSelectElement(event):
        global selectedElement, selectedTable
        if selectedTable.get() != 'Результат запроса' and table.selection(): 
            selectedElement = table.selection()[0]

    def keyboardScroll(event):
        if event.keysym == 'Up':
            table.yview_scroll(-1, "units")
        elif event.keysym == 'Down':
            table.yview_scroll(1, "units")
        elif event.keysym == 'Left':
            table.xview_scroll(-10, "units")
        elif event.keysym == 'Right':
            table.xview_scroll(10, "units")

    table = ttk.Treeview(parent, show='headings', selectmode='browse')
    table.place(height=587, width=700, x=0, y=0)

    table.bind('<ButtonRelease-1>', onSelectElement)
    table.bind("<KeyPress>", keyboardScroll)

    return table

def addTableChoice(parent):
    def onSelect(event):
        global colnames
        data, colnames = getTableData(conn, selectedTable.get())
        updateTable(data, colnames)
        blockCRUD(False)
    
    frame = tk.Frame(parent, background='#FCCBE0')

    label = ttk.Label(frame, text='Выбранная таблица:', background='#FCCBE0')
    label.pack()
    selectedTable = tk.StringVar(parent)

    style = ttk.Style()
    style.configure('TMenubutton', background='#D1A9BA', borderwidth=2)

    options = getAllTables(conn)
    options.append(options[0])
    drop = ttk.OptionMenu(frame, selectedTable, *options, command=onSelect)
    drop.pack(pady=3)

    frame.place(height=100, width=200, x=700, y=10)

    selectedTable.set('Выбор')

    return selectedTable

def addCRUDButtons(parent):
    frame = tk.Frame(parent, background='#FCCBE0', pady=5)
    addButton = tk.Button(frame, text="Добавить запись", height=80, background='#D1A9BA',
                          command= lambda: createAddWindow(parent), state=tk.DISABLED)
    removeButton = tk.Button(frame, text="Удалить запись", height=80, background='#D1A9BA',
                             command= lambda: createRemoveWindow(parent), state=tk.DISABLED)
    updateButton = tk.Button(frame, text="Изменить запись", height=80, background='#D1A9BA',
                             command=lambda: createUpdateWindow(parent), state=tk.DISABLED)

    frame.place(height=220, width=200, x=700, y=65)
    addButton.place(height=60, width=190, x=5, y=0)
    removeButton.place(height=60, width=190, x=5, y=70)
    updateButton.place(height=60, width=190, x=5, y=140)

    return (addButton, removeButton, updateButton)

def createAddWindow(parent):
    window = tk.Toplevel(parent, background='#FCCBE0', pady=20)
    window.title("Добавить запись")
    height = len(colnames) * 80 + 50
    window.geometry(f'300x{height}+1000+100')
    window.resizable(False, False)

    def addValues():
        values = [textField.get() for textField in textFields]

        keyString = ''
        for column in colnames[:-1]:
            keyString += f'{column}, '
        keyString += colnames[-1]
        keyString = f"({keyString})"
        
        result = addRecord(conn, selectedTable.get(), keyString, tuple(values))
        if result is None:
            table.insert('', tk.END, values=values)
            sortRecords(0, False)
            window.destroy()
        else:
            messagebox.showerror("Ошибка", result)

    mainFrame = tk.Frame(window, background='#FCCBE0')
    mainFrame.pack()
    textFields = []

    for field in colnames:
        frame = tk.Frame(mainFrame, background='#FCCBE0')
        frame.pack()
        label = ttk.Label(frame, text=f'{field}:', background='#FCCBE0', font=('Helvetica', 10))
        label.pack()
        textField = ttk.Entry(frame, background='#FCCBE0')
        textField.pack(pady=5)
        textFields.append(textField)

    confirm = tk.Button(window, text="Добавить", command=addValues, background='#D1A9BA')
    confirm.pack(pady=2)

def createRemoveWindow(parent):
    if selectedElement is None:
        return
    
    values = table.item(selectedElement, 'values')

    paramString = ''
    for i in range(len(colnames) - 1):
        paramString += f'{colnames[i]} = \'{values[i]}\' AND '
    paramString += f'{colnames[-1]} = \'{values[-1]}\''

    result = deleteRecord(conn, selectedTable.get(), paramString)
    if result is None:
        table.delete(selectedElement)
    else:
        messagebox.showerror("Ошибка", result)

def createUpdateWindow(parent):
    if selectedElement is None:
        return 
    
    window = tk.Toplevel(parent, background='#FCCBE0', pady=20)
    window.title("Изменить запись")
    height = len(colnames) * 80 + 50
    window.geometry(f'300x{height}+1000+100')
    window.resizable(False, False)

    values = table.item(selectedElement, 'values')

    paramString = ''
    for i in range(len(colnames) - 1):
        paramString += f'{colnames[i]} = \'{values[i]}\' AND '
    paramString += f'{colnames[-1]} = \'{values[-1]}\''

    def updateValues():
        newValues = [textField.get() for textField in textFields]

        setString = ''
        for i in range(len(colnames) - 1):
            setString += f'{colnames[i]} = \'{newValues[i]}\', '
        setString += f'{colnames[-1]} = \'{newValues[-1]}\''
        
        result = updateRecord(conn, selectedTable.get(), setString, paramString)
        if result is None:
            table.item(selectedElement, value=newValues)
            table.update_idletasks()
            window.destroy()
        else:
            messagebox.showerror("Ошибка", result)

    mainFrame = tk.Frame(window, background='#FCCBE0')
    mainFrame.pack()
    textFields = []

    count = 0
    for field in colnames:
        frame = tk.Frame(mainFrame, background='#FCCBE0')
        frame.pack()

        label = ttk.Label(frame, text=f'{field}:', background='#FCCBE0', font=('Helvetica', 10))
        label.pack()

        textField = ttk.Entry(frame, background='#FCCBE0')
        textField.pack(pady=5)
        textField.insert(0, values[count])
        textFields.append(textField)

        count += 1

    confirm = tk.Button(window, text="Изменить", command=updateValues, background='#D1A9BA')
    confirm.pack(pady=2)

def addQueryChoice(parent):
    choiceButton = tk.Button(parent, text="Вывести список запросов", background='#D1A9BA',
                             command= lambda: queryChoiceWindow(parent))
    
    choiceButton.place(height=60, width=190, x=705, y=520)

def queryChoiceWindow(parent):
    def createCallback(query):
        def callback():
            global colnames
            data, colnames = runQuery(conn, query)
            updateTable(data, colnames)
            blockCRUD(True)
            selectedTable.set('Результат запроса')
            window.destroy()
        return callback
    
    def configScroll(event):
        canvas.configure(scrollregion=canvas.bbox("all"))

    def onScroll(event):
        if 'canvas' in str(event.widget):
            canvas.yview_scroll(int(-1*(event.delta/120)), "units")

    window = tk.Toplevel(parent, background='#FCCBE0')
    window.title("Список запросов")
    window.geometry(f'320x520+1000+100')
    window.resizable(False, False)

    canvas = tk.Canvas(window, background='#FCCBE0')
    frame = tk.Frame(canvas, background='#FCCBE0')
    scroll = ttk.Scrollbar(canvas, orient=tk.VERTICAL, command=canvas.yview)

    canvas.configure(yscrollcommand=scroll.set, highlightthickness=0)
    scroll.pack(side=tk.RIGHT, fill=tk.Y)

    btnsInfo = getButtonInfo()
    for entry in btnsInfo:
        callback = createCallback(entry[1])
        btn1 = tk.Button(frame, text=entry[0], padx=5, pady=2, background='#D1A9BA',
                         cursor='hand2', width=260, justify='left', 
                         anchor='w', wraplength=250, command=callback)
        btn1.pack(pady=2)

    canvas.create_window((0,0), window=frame, width=270)
    frame.bind("<Configure>", configScroll)
    canvas.configure(scrollregion=canvas.bbox('all'), background='#FCCBE0',)

    canvas.place(height=490, width=300, x=10, y=15)
    canvas.update_idletasks()
    canvas.yview_moveto(0)

    canvas.bind_all("<MouseWheel>", onScroll)

def updateTable(data, columns):
    global table, selectedElement
    clearTable()
    selectedElement = None
    
    table['columns'] = list(range(0, len(columns)))

    count = 0
    for column in columns:
        table.column(str(count), minwidth=50, width=150, stretch=tk.NO)
        table.heading(str(count), text=column, command=lambda count=count: sortRecords(count, False))
        count += 1
    for record in data:
        table.insert('', tk.END, values=record)
        
def clearTable():
    global table
    for item in table.get_children():
        table.delete(item)   

def sortRecords(column, rev):
    global table
    records = [(table.set(k, column), k) for k in table.get_children("")]

    try:
        records = [(float(record[0]), record[1]) for record in records]
    except ValueError:
        pass  

    if all(isinstance(record[0], (int, float)) for record in records):  
        records.sort(key=lambda x: float(x[0]), reverse=rev)
    else:  
        records.sort(key=lambda x: str(x[0]), reverse=rev)

    for index,  (_, k) in enumerate(records):
        table.move(k, "", index)

    table.heading(column, command=lambda: sortRecords(column, not rev))

def blockCRUD(block):
    global CRUDbuttons
    for button in CRUDbuttons:
        button.config(state=tk.DISABLED if block else tk.NORMAL)

# ----------------------------------

selectedElement = None
conn = initConnection()
root, table, CRUDbuttons, selectedTable = initWindow()
colnames = None
root.mainloop()