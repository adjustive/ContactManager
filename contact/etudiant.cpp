#include <QtGui/QApplication>
#include <QDebug>
#include <fstream>
#include <stdlib.h>
#include <string>
#include "etudiant.h"
#include <iostream>
#include <QFile>
#include <QTextStream>

int nbEtudiant(){
        QString fileName = "eleves.txt";
        QFile fichier(fileName);
        int nb = 0;
        if(fichier.open(QIODevice::ReadOnly | QIODevice::Text)){
                QTextStream flux(&fichier);


                while (!flux.atEnd())
                {
                        flux.readLine();
                        nb++;

                }

        }
      //  qDebug() << nb;
        return(nb+1);

}
void enregistrer(Etudiant e){
    QString fileName = "eleves.txt";
    QFile fichier(fileName);
    fichier.open(QIODevice::WriteOnly | QIODevice::Append| QIODevice::Text);
    QTextStream flux(&fichier);
   // qDebug() << e.who();
   // qDebug() << "lol";
    flux << e.who();
    fichier.flush();
    fichier.close();

}

Etudiant chercher(QString identifiant){
        QString  mat, nom, prenom, adres, email;
        QString fileName = "eleves.txt";
        QFile fichier(fileName);

        if(fichier.open(QIODevice::ReadOnly | QIODevice::Text)){
                QTextStream flux(&fichier);


                while (!flux.atEnd())
                {
                        QString line = flux.readLine();
                        if (line.contains(identifiant, Qt::CaseInsensitive)){

                            int i = 0;
                            while(line[i] != '/')
                                    mat.push_back(line[i++]);
                            i++;
                            while(line[i] != '/')
                                    nom.push_back(line[i++]);
                            i++;
                            while(line[i] != '/')
                                    prenom.push_back(line[i++]);
                            i++;
                            while(line[i] != '/')
                                    adres.push_back(line[i++]);
                            i++;
                            while(line[i] != '\0')
                                    email.push_back(line[i++]);
                            Etudiant b(mat, nom, prenom, adres, email);
                            return(b);
                        }

                 }
            }
          else
             // qDebug()<<"Nothing Found"<<endl;
              return(Etudiant());




}
void supprimer(Etudiant e){


        QString aSupprimer = e.getMat(), ligne, buffer;
        QString fileName = "eleves.txt";
        QFile fichier(fileName);

        if(fichier.open(QIODevice::ReadOnly | QIODevice::Text)){
                QTextStream flux(&fichier);


                while (!flux.atEnd())
                {
                        QString line = flux.readLine();
                        Etudiant m(line);
                       // qDebug() << aSupprimer << m.getMat();
                        //if (!line.contains(aSupprimer, Qt::CaseInsensitive)){
                        if ( QString::compare(aSupprimer, m.getMat(), Qt::CaseInsensitive)){
                            buffer += line+"\n";
                          //  qDebug()<<"buff " << buffer;
                            //qDebug() <<"line "<< line;
                        }

                 }
            }
        fichier.close();
        if(fichier.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text)){
             QTextStream flux(&fichier);
             flux << buffer;
             flux.flush();
        }


}
void listeEtudiants(){
        std::vector<Etudiant> E;
        std::vector<Etudiant>::iterator it;
        QString fileName = "eleves.txt";
        QFile fichier(fileName);

        if(fichier.open(QIODevice::ReadOnly | QIODevice::Text)){
                QTextStream flux(&fichier);


                while (!flux.atEnd())
                {
                        QString line = flux.readLine();
                        E.push_back(line);

                }
       }
        for(it = E.begin(); it != E.end(); it++){
//                qDebug()<<"-------------------------------"<<endl;
                it->affiche();
                //qDebug()<<"-------------------------------"<<endl;
        }
        fichier.close();

}

void ajouter(){
/*        string mat, n,p,a,na;
        qDebug()<<"Saisissez le matricule de l'etudiant"<< endl;
        cin >> mat;
        qDebug()<<"Saisissez le nom de l eleve"<<endl;
        cin >> n;
        qDebug()<<"Saisissez le prenom de l eleve"<<endl;
        cin >> p;
        qDebug()<<"Saisissez l numero de l eleve"<<endl;
        cin >> a;
        qDebug()<<"Saisissez la nationnalite de l eleve"<<endl;
        cin >> na;
  */      Etudiant e("EPI", "Landry", "kienteg", "Dakar", "Senegal");
        enregistrer(e);
}

Etudiant::Etudiant(QString ma, QString no, QString p, QString a, QString na)
{
        matricule = ma;
        nom = no, prenom = p, numero = a, email = na;
}
Etudiant::Etudiant(QString no, QString p, QString a, QString na)
{
        matricule = QString::number(nbEtudiant());
        nom = no, prenom = p, numero = a, email = na;
}
Etudiant::Etudiant()
{
        matricule = "";
        nom = "", prenom = "", numero = "", email = "";
}

Etudiant::Etudiant(QString ligne)
{
        int i = 0;
                                while(ligne[i] != '/')
                                        matricule.push_back(ligne[i++]);
                                i++;
                                while(ligne[i] != '/')
                                        nom.push_back(ligne[i++]);
                                i++;
                                while(ligne[i] != '/')
                                        prenom.push_back(ligne[i++]);
                                i++;
                                while(ligne[i] != '/')
                                        numero.push_back(ligne[i++]);
                                i++;
                                while(ligne[i] != '\0')
                                        email.push_back(ligne[i++]);

}

QString Etudiant::who(void)
{
        return(matricule + "/"+ nom + "/"+ prenom+ "/"+ numero + "/"+ email+"\n" );
}

void Etudiant::affiche(void)
{
        //qDebug() << "Matricule: "+matricule + "\n Nom: "+ nom + " Prenom: "+ prenom+ "\n Numero: "+ numero + "\n email: "+ email <<endl;
}
QString Etudiant::getMat()
{
        return(matricule);
}



QString Etudiant::getNom(){
    return(nom);
}

QString Etudiant::getPrenom(){
    return(prenom);
}

QString Etudiant::getNum(){
    return(numero);
}

QString Etudiant::getEmail(){
    return(email);
}
void modifierEtudiant(QString mat,QString n, QString p, QString num, QString mail){

    QString buffer;
    QString fileName = "eleves.txt";
    QFile fichier(fileName);
    Etudiant e(mat,n,p,num,mail);
    if(fichier.open(QIODevice::ReadOnly | QIODevice::Text)){
            QTextStream flux(&fichier);


            while (!flux.atEnd())
            {
                    QString line = flux.readLine();
                    Etudiant f(line);

                    if (f.getMat() == mat)
                        buffer += e.who();

                    else
                        buffer += line+"\n";
                  /*if (!line.contains(aModifier, Qt::CaseInsensitive)){
                        buffer += ligne+"\n";
                    }
                    else{
                        Etudiant e()

             }*/
        }
    fichier.close();
    if(fichier.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text)){
         QTextStream flux(&fichier);
         flux << buffer;
    }


}
}
