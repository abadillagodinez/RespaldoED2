#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(this->width(), this->height());
    move(500, 250);
    QObject::connect(logic, SIGNAL(cambiarLabel(int)), this, SLOT(pintarLabel(int)));
    QObject::connect(logic, SIGNAL(moverLabels(int)), this, SLOT(atender(int)));
    logic->start();

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::mover(){
    QPropertyAnimation *animation = new QPropertyAnimation(this, "geometry");
    animation->setDuration(1000);
    animation->setStartValue(QRect(500, 250, 100, 30));
    animation->setEndValue(QRect(0, 0, 100, 30));
    animation->start();
}

void MainWindow::pintarLabel(int index){
    switch (index) {
    case 0:
        ui->lblEstudiante1->setText("1");
        break;
    case 1:
        ui->lblEstudiante2->setText("2");
        break;
    case 2:
        ui->lblEstudiante3->setText("3");
        break;
    case 3:
        ui->lblEstudiante4->setText("4");
        break;
    case 4:
        ui->lblEstudiante5->setText("5");
        break;
    case 5:
        ui->lblEstudiante6->setText("6");
        break;
    case 6:
        ui->lblEstudiante7->setText("7");
        break;
    case 7:
        ui->lblEstudiante8->setText("8");
        break;
    case 8:
        ui->lblEstudiante9->setText("9");
        break;
    case 9:
        ui->lblEstudiante10->setText("10");
        break;
    }
}

void MainWindow::wait(){
    clock_t startTime = clock(); //Start timer
    double secondsPassed;
    double secondsToDelay = 1;
    bool flag = true;
    while(flag){
        secondsPassed = (clock() - startTime) / CLOCKS_PER_SEC;
        if(secondsPassed >= secondsToDelay){
            flag = false;
            cout << "han pasado " << secondsPassed << " sec" << endl;
        }
    }
}

void MainWindow::atender(int mostrador){

    switch (mostrador) {
    case 1:
        ui->lblMostrador1->setText(ui->lblEstudiante1->text());
        ui->lblEstudiante1->setText(ui->lblEstudiante2->text());
        ui->lblEstudiante2->setText(ui->lblEstudiante3->text());
        ui->lblEstudiante3->setText(ui->lblEstudiante4->text());
        ui->lblEstudiante4->setText(ui->lblEstudiante5->text());
        ui->lblEstudiante5->setText(ui->lblEstudiante6->text());
        ui->lblEstudiante6->setText(ui->lblEstudiante7->text());
        ui->lblEstudiante7->setText(ui->lblEstudiante8->text());
        ui->lblEstudiante8->setText(ui->lblEstudiante9->text());
        ui->lblEstudiante9->setText(ui->lblEstudiante10->text());
        ui->lblEstudiante10->setText("");
        break;
    case 2:
        ui->lblMostrador2->setText(ui->lblEstudiante1->text());
        ui->lblEstudiante1->setText(ui->lblEstudiante2->text());
        ui->lblEstudiante2->setText(ui->lblEstudiante3->text());
        ui->lblEstudiante3->setText(ui->lblEstudiante4->text());
        ui->lblEstudiante4->setText(ui->lblEstudiante5->text());
        ui->lblEstudiante5->setText(ui->lblEstudiante6->text());
        ui->lblEstudiante6->setText(ui->lblEstudiante7->text());
        ui->lblEstudiante7->setText(ui->lblEstudiante8->text());
        ui->lblEstudiante8->setText(ui->lblEstudiante9->text());
        ui->lblEstudiante9->setText(ui->lblEstudiante10->text());
        ui->lblEstudiante10->setText("");
        break;
    case 3:
        ui->lblMostrador3->setText(ui->lblEstudiante1->text());
        ui->lblEstudiante1->setText(ui->lblEstudiante2->text());
        ui->lblEstudiante2->setText(ui->lblEstudiante3->text());
        ui->lblEstudiante3->setText(ui->lblEstudiante4->text());
        ui->lblEstudiante4->setText(ui->lblEstudiante5->text());
        ui->lblEstudiante5->setText(ui->lblEstudiante6->text());
        ui->lblEstudiante6->setText(ui->lblEstudiante7->text());
        ui->lblEstudiante7->setText(ui->lblEstudiante8->text());
        ui->lblEstudiante8->setText(ui->lblEstudiante9->text());
        ui->lblEstudiante9->setText(ui->lblEstudiante10->text());
        ui->lblEstudiante10->setText("");
        break;
    default:
        break;
    }


}

bool MainWindow::is_int(string valor) {
    cout << "Valor es: " << valor << endl;
    std::stringstream str(valor);
    int f;
    return bool(str >> f);
}

void MainWindow::on_btnProfesoresDeUnCurso_clicked()
{
    if(ui->txfCarreraParaProfesores->text().isEmpty() || ui->txfCursosParaProfesores->text().isEmpty()){
        QMessageBox::information(this, "Error", "Alguno de los campos esta vacio");
    }
    else if(!ui->txfCarreraParaProfesores->text().toInt() || !ui->txfCursosParaProfesores->text().toInt()){
        QMessageBox::information(this, "Error", "Alguno de los valores no es un entero");
    }
    else{
        //aqui va el codigo que genera el reporte
    }
}

void MainWindow::on_btnCursosDeUnaCarrera_clicked()
{
    if(ui->txfCarreraParaCursos->text().isEmpty()){
        QMessageBox::information(this, "Error", "El campo esta vacio");
    }
    else if(!ui->txfCarreraParaCursos->text().toInt()){
        QMessageBox::information(this, "Error", "El valor no es un entero");
    }
    else{
        //aqui va el codigo que genera el reporte
    }
}

void MainWindow::on_btnEstudianteDeUnGrupo_clicked()
{
    if(ui->txfCarreraParaEstudiantes->text().isEmpty() || ui->txfCursosParaEstudiantes->text().isEmpty() || ui->txfGrupoParaEstudiantes->text().isEmpty()){
        QMessageBox::information(this, "Error", "Alguno de los campos esta vacio");
    }
    else if(!ui->txfCarreraParaEstudiantes->text().toInt() || !ui->txfCursosParaEstudiantes->text().toInt() || !ui->txfGrupoParaEstudiantes->text().toInt()){
        QMessageBox::information(this, "Error", "Alguno de los valores no es un entero");
    }
    else{
        //aqui va el codigo que genera el reporte
    }
}

void MainWindow::on_btnEstudiantesDeUnCarrera_clicked()
{
    if(ui->txfCarreraParaEstudiantes2->text().isEmpty()){
        QMessageBox::information(this, "Error", "El campo esta vacio");
    }
    else if(!ui->txfCarreraParaEstudiantes2->text().toInt()){
        QMessageBox::information(this, "Error", "El valor no es un entero");
    }
    else{
        //aqui va el codigo que genera el reporte
    }
}

void MainWindow::on_btnProfesoresDeUNACarrera_clicked()
{
    if(ui->txfCarreraParaProfesores2->text().isEmpty()){
        QMessageBox::information(this, "Error", "El campo esta vacio");
    }
    else if(!ui->txfCarreraParaProfesores2->text().toInt()){
        QMessageBox::information(this, "Error", "El valor no es un entero");
    }
    else{
        //aqui va el codigo que genera el reporte
    }
}
