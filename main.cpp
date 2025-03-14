#include "Teste.h"
#include "Repository.h"
#include "Service.h"
#include "GUI.h"
#include "ListaNotificare.h"
#include <QApplication>
int main (int argc, char * argv[]){
    Teste::run_all_tests();
    QApplication app(argc,argv);
    AbstractRepository* repo = new FileRepository(R"(E:\Folders\UBB An 1 sem 2\Qtie\apartamente.txt)");
    ListaNotificare listaNotificare;
    Service service(*repo,listaNotificare);
    auto* gui = new LocatariGUI(service);
    gui->show();
    return app.exec();
}