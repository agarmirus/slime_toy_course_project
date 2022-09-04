from PyQt5 import uic
from PyQt5.QtWidgets import QMainWindow, QApplication
import sys

class MainWindow(QMainWindow):
   def __init__(self):
      super(MainWindow, self).__init__()
      uic.loadUi('mainwindow.ui', self)


app = QApplication(sys.argv)

w = MainWindow()
w.show()

sys.exit(app.exec_())

