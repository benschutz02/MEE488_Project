from PyQt5.QtWidgets import *
import sys
import serial
import serial.tools.list_ports
import time



# app setup
app = QApplication(sys.argv)
dlayout = QGridLayout()
ilayout = QGridLayout()

u_text = ['lbs','kg']  # units for force
d_list = ['Phone','Tablet','Laptop']  # device list
title = 'Drop/Impact Testing'  # app title

reset1 = QPushButton('Reset')  # reset for drop
reset2 = QPushButton('Reset')  # reset for impact
time.sleep(0.5)


## FUNCTIONS ##
def write_read(x):
    # start time
    start = time.time()

    # arduino setup
    ports = [comport.device for comport in serial.tools.list_ports.comports()]

    # connect to port
    try:
        arduino = serial.Serial(port=ports[0], baudrate=9600, timeout=1)
    except IndexError:
        return 'n/a',0.00000

    # convert to string
    val = str(x)

    # write, then receive data
    arduino.write(val.encode('utf-8'))
    data = arduino.readline().decode()
    arduino.close()

    # calculate runtime
    end = time.time()
    runtime = end - start

    return data, runtime

def unitsChanged2():
    global u_text,uval2,fval,sval2

    value = uval2.currentText()

    if value == 'Imperial':
        fval.setSuffix(f' {u_text[0]}')
    else:
        fval.setSuffix(f' {u_text[1]}')


    # update Status
    sval2.append(f'Units Set ({value})')

def raisePressed():
    global sval

    data, runtime = write_read(1)

    if data == 'n/a':
        sval.append(f'System Not Connected. Reattach USB Cable')
        return data

    # update status
    print(data)
    sval.append(f'Raising Carriage to Drop Height ({runtime:.3}s)')
    return data

def raisePressed2():
    global sval2

    data, runtime = write_read(1)

    if data == 'n/a':
        sval2.append(f'System Not Connected. Reattach USB Cable')
        return data

    # update status
    print(data)
    sval2.append(f'Raising Carriage to Drop Height ({runtime:.3}s)')
    return data

def releasePressed():
    global sval,dval

    data, runtime = write_read(2)

    if data == 'n/a':
        sval.append(f'System Not Connected. Reattach USB Cable')
        return data

    # update status
    sval.append(f'{dval.currentText()} Released ({runtime:.3}s)')
    return data

def releasePressed2():
    global sval2,fval

    data, runtime = write_read(3)

    if data == 'n/a':
        sval2.append(f'System Not Connected. Reattach USB Cable')
        return data

    # update status
    sval2.append(f'{fval.value()}{fval.suffix()} Carriage Released ({runtime:.3}s)')
    return data

def itemSet():
    global d_list,dval,sval

    value = dval.currentText()

    # set timing of actuators
    data, run1 = write_read(4)  # item set call in arduino

    if data == 'n/a':
        sval.append(f'System Not Connected. Reattach USB Cable')
        return data

    # determine what device to send
    if value == 'Phone':
        x = 1
    elif value == 'Tablet':
        x = 2
    elif value == 'Laptop':
        x = 3

    data2, run2 = write_read(x)

    # calculate final runtime
    runtime = run1 + run2

    # update Status
    sval.append(f'{value} Set ({runtime:.3}s)')

def itemSet2():
    global d_list, dval, sval

    time.sleep(0.5)

    # update Status
    sval2.append('Impact Weight Set')


def resetPressed():
    global sval

    data, runtime = write_read(1)

    if data == 'n/a':
        sval.append(f'System Not Connected. Reattach USB Cable')
        return data

    data2, runtime2 = write_read(2)

    # time to execute
    run = runtime + runtime2

    # update status
    sval.append(f'System Reset ({run:.3}s)')


def resetPressed2():
    global sval2

    data, runtime = write_read(5)

    if data == 'n/a':
        sval2.append(f'System Not Connected. Reattach USB Cable')
        return data

    data2, runtime2 = write_read(1)

    # time to execute
    run = runtime + runtime2

    # update status
    sval2.append(f'System Reset ({run:.3}s)')




## DROP TESTING TAB ##
drop = QGroupBox()

# make height box, widget, then add to box
height = QGroupBox('Height:')
lay = QVBoxLayout()

hval = QPushButton('Raise')

lay.addWidget(hval)
height.setLayout(lay)


# make device list, widget, and add to box
device = QGroupBox('Device:')
lay = QHBoxLayout()

dval = QComboBox()
dval.addItems(d_list)

attach = QPushButton('Attach')

lay.addWidget(dval)
lay.addWidget(attach)
device.setLayout(lay)


# status section
status = QGroupBox('Status')
lay = QVBoxLayout()

sval = QTextEdit()
sval.setReadOnly(True)

#### STATUS UPDATES ####
sval.append('System Initialized')
#### STATUS UPDATES ####


lay.addWidget(sval)
status.setLayout(lay)

# last buttons
release = QPushButton("Release")




## IMPACT TESTING TAB ##
impact = QGroupBox()

# using mostly the same things as drop, but trading force for device
force = QGroupBox('Weight:')
lay = QHBoxLayout()

fval = QDoubleSpinBox()
fval.setSingleStep(1)
fval.setRange(0,1000)
fval.setSuffix(f' {u_text[0]}')

set = QPushButton('Set')

lay.addWidget(fval)
lay.addWidget(set)

force.setLayout(lay)

# make height box, widget, then add to box
height2 = QGroupBox('Height:')
lay = QVBoxLayout()

hval2 = QPushButton('Raise')

lay.addWidget(hval2)
height2.setLayout(lay)


# make unit list, widget, add to box
units2 = QGroupBox('Units:')
lay = QVBoxLayout()

uval2 = QComboBox()
uval2.addItems(['Imperial','Metric'])

lay.addWidget(uval2)
units2.setLayout(lay)


# status section
status2 = QGroupBox('Status')
lay = QVBoxLayout()

sval2 = QTextEdit()
sval2.setReadOnly(True)
#### STATUS UPDATES ####
sval2.append('System Initialized')
#### STATUS UPDATES ####

lay.addWidget(sval2)
status2.setLayout(lay)

# last buttons
release2 = QPushButton("Release")




## TAB LAYOUT ##

# drop tab layout
dlayout.addWidget(height,0,0)
dlayout.addWidget(device,0,1)

dlayout.addWidget(status,1,0,2,2)

dlayout.addWidget(release,1,2)
dlayout.addWidget(reset1,2,2)

drop.setLayout(dlayout)


# impact tab layout
ilayout.addWidget(height2,0,0)
ilayout.addWidget(force,0,1)
ilayout.addWidget(units2,0,2)

ilayout.addWidget(status2,1,0,2,2)

ilayout.addWidget(release2,1,2)
ilayout.addWidget(reset2,2,2)

impact.setLayout(ilayout)




## connect functionality ##

# unit dropdown
uval2.activated[str].connect(unitsChanged2)

# reset buttons
reset1.clicked.connect(resetPressed)
reset2.clicked.connect(resetPressed2)

# release buttons
release.clicked.connect(releasePressed)
release2.clicked.connect(releasePressed2)

# height buttons
hval.clicked.connect(raisePressed)
hval2.clicked.connect(raisePressed2)

# attach and set buttons
attach.clicked.connect(itemSet)
set.clicked.connect(itemSet2)


# make tabs, add title
window = QTabWidget()
window.addTab(drop,'Drop')
window.addTab(impact,'Impact')

window.setWindowTitle(title)

# start app
window.show()
app.exec()





