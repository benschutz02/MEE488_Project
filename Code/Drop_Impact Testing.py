from PyQt5.QtWidgets import *
import sys


# generic setup
app = QApplication(sys.argv)
dlayout = QGridLayout()
ilayout = QGridLayout()

u_text = ['lbs','kg']  # units for force
d_list = ['Phone','Tablet','Laptop']  # device list
title = 'Drop/Impact Testing'  # app title

reset1 = QPushButton('Reset')  # reset for drop
reset2 = QPushButton('Reset')  # reset for impact

## FUNCTIONS ##
def unitsChanged2():
    global u_text,uval2,hval2,fval,sval2

    value = uval2.currentText()

    if value == 'Imperial':
        fval.setSuffix(f' {u_text[0]}')
    else:
        fval.setSuffix(f' {u_text[1]}')


    # update Status
    sval2.append(f'Units Set ({value})')

def resetPressed():
    global sval
    # start time

    # set height to 4 ft

    # open drop arms

    # calculate time to complete

    # update status
    sval.append('System Reset')

def resetPressed2():
    global sval2
    # start time

    # set height to 3 ft, zero force

    # open drop arms

    # calculate time to complete

    # update status
    sval2.append('System Reset')

def releasePressed():
    global sval

    # update status
    sval.append(f'{dval.currentText()} Released (00s)')

def releasePressed2():
    global sval2,fval,u_text

    # update status
    sval2.append(f'{fval.value()}{fval.suffix()} Carriage Released (00s)')

def raisePressed():
    global sval

    # update status
    sval.append('Carriage Raised to Drop Height')

def raisePressed2():
    global sval2

    # update status
    sval2.append('Carriage Raised to Drop Height')

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


# make tabs, add title
window = QTabWidget()
window.addTab(drop,'Drop')
window.addTab(impact,'Impact')

window.setWindowTitle(title)

# start app
window.show()
app.exec()





