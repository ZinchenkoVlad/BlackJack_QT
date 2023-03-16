#include "gamewidget.h"
#include "ui_gamewidget.h" // Include the generated header file for the UI

Player user(100);
Player dealer;

GameWidget::GameWidget(QWidget *parent)
    : QWidget(parent), ui(new Ui::GameWidget)
{
    ui->setupUi(this); // Load the UI from the .ui file

    QPixmap pixmapMute(":/icons/Assets/soundUnmute.png");
    QIcon ButtonIconMute(pixmapMute);
    ui->btnMute->setIcon(ButtonIconMute);
    ui->btnMute->setIconSize(QSize(35, 35));

    backgroundMusic = new QMediaPlayer;
    audioOutput1 = new QAudioOutput;

    backgroundMusic->setAudioOutput(audioOutput1);
    backgroundMusic->setSource(QUrl::fromLocalFile("qrc:/sound/Assets/sound/game-setting-fantasy.mp3"));
    audioOutput1->setVolume(5);

    backgroundMusic->setLoops(QMediaPlayer::Infinite);
    backgroundMusic->play();

    startGame();
}

GameWidget::~GameWidget()
{
    delete ui;
    delete backgroundMusic;
    delete audioOutput1;
    delete music;
    delete audioOutput;
}

void GameWidget::startGame()
{
    makeBet();
    reset();

    Card a0(randomCardGenerator(), pathForFrontImg, pathForBackImg, true);
    Card a1(randomCardGenerator(), pathForFrontImg);
    Card a2(randomCardGenerator(), pathForFrontImg);
    Card a21(randomCardGenerator(), pathForFrontImg, pathForBackImg, true);
    dealer.setPathToBackCardImg(a21.getPathToBackCardImg());
    Card a22(randomCardGenerator(), pathForFrontImg);

    QPixmap pixa0(a0.getPathToCardImg());
    ui->labelBackSide->setPixmap(pixa0.scaled(100, 170));

    drawCard(&user, &a1, ui->labelPlayer1, ui->labelPlayerScore, animation1, 20, 380);
    drawCard(&user, &a2, ui->labelPlayer2, ui->labelPlayerScore, animation2, 130, 380);
    drawCard(&dealer, &a21, ui->labelDealer1, ui->labelDealerScore, animation21, 20, 20);
    drawCard(&dealer, &a22, ui->labelDealer2, ui->labelDealerScore, animation22, 130, 20);


    // hit/stand btn is next
}

void GameWidget::reset(){
    countOfPressHit = 1;
    ui->labelPlayer1->clear();
    ui->labelPlayer2->clear();
    ui->labelPlayer3->clear();
    ui->labelPlayer4->clear();
    ui->labelPlayer5->clear();
    ui->labelPlayer6->clear();
    ui->labelDealer1->clear();
    ui->labelDealer2->clear();
    ui->labelDealer3->clear();
    ui->labelDealer4->clear();
    ui->labelDealer5->clear();
    ui->labelDealer6->clear();

    user.setAmountOfPoints(0);
    dealer.setAmountOfPoints(0);

    ui->labelDealerScore->setText(QString::number(user.getAmountOfPoints()));
    ui->labelPlayerScore->setText(QString::number(user.getAmountOfPoints()));

    ui->btnHit->setEnabled(true);
    ui->btnStand->setEnabled(true);

    initAnimation();

    ui->labelPlayerBet->setText("Your bet: " + QString::number(user.getPlayerBet()));
    firstTimeForMakeBet = false;

    pathForFrontImg = updatedPathForFrontImg;
    pathForBackImg = updatedPathForBackImg;
}

void GameWidget::initAnimation(){
    animation1  = new QPropertyAnimation(ui->labelPlayer1, "geometry");
    animation2  = new QPropertyAnimation(ui->labelPlayer2, "geometry");
    animation3  = new QPropertyAnimation(ui->labelPlayer3, "geometry");
    animation4  = new QPropertyAnimation(ui->labelPlayer4, "geometry");
    animation5  = new QPropertyAnimation(ui->labelPlayer5, "geometry");
    animation6  = new QPropertyAnimation(ui->labelPlayer6, "geometry");
    animation21 = new QPropertyAnimation(ui->labelDealer1, "geometry");
    animation22 = new QPropertyAnimation(ui->labelDealer2, "geometry");
    animation23 = new QPropertyAnimation(ui->labelDealer3, "geometry");
    animation24 = new QPropertyAnimation(ui->labelDealer4, "geometry");
    animation25 = new QPropertyAnimation(ui->labelDealer5, "geometry");
    animation26 = new QPropertyAnimation(ui->labelDealer6, "geometry");
}

void GameWidget::soundPlayer(QString path){
    music = new QMediaPlayer;
    audioOutput = new QAudioOutput;
    music->setAudioOutput(audioOutput);
    music->setSource(QUrl::fromLocalFile(path));
    audioOutput->setVolume(50);
    if(isMuted) audioOutput->setVolume(0);
    music->play();
}

void GameWidget::makeBet(){

    int playerMoney = user.getAmountOfMoney();

    QInputDialog dialog(this);
    dialog.setWindowTitle("Make your bet");
    dialog.setLabelText("Make your bet\nYour bank: " + QString::number(playerMoney));
    dialog.setInputMode(QInputDialog::IntInput);
    dialog.setIntRange(1, playerMoney);
    dialog.setIntStep(1);
    dialog.setIntValue(playerStartupBet);
    dialog.setOkButtonText("Place Bet");
    dialog.setCancelButtonText("Exit");

    // Show the dialog and get the user's bet
    bool ok = dialog.exec();
    int playerBet = dialog.intValue();

    if(firstTimeForMakeBet){
        dialog.setOptions(QInputDialog::NoButtons);
    }

    if (ok) {
        if (playerMoney == 0) {
            messageInfo("Information", "Your bank is empty.\nYou must leave.", "");
            QCoreApplication::quit();
            return;
        }
        else {
            user.setPlayerBet(playerBet);
            playerStartupBet = playerBet;
        }
    }
    else {
        if(firstTimeForMakeBet){
            messageInfo("Information", "You should play, do not leave so fast.", "");
            makeBet();
            return;
        }
        QCoreApplication::quit();
    }
}

std::tuple <QString, QString> GameWidget::randomCardGenerator(){
    static const QStringList cardTypes = {"clubs", "diamonds", "hearts", "spades"};
    QString cardNum;
    QString cardType;

    QSet<QString> usedCards(listOfUsedCards.begin(), listOfUsedCards.end());
    do {
        cardNum = QString::number(QRandomGenerator::global()->bounded(2, 15));
        cardType = cardTypes[QRandomGenerator::global()->bounded(0, 4)];
    } while (usedCards.contains(cardNum + cardType));

    listOfUsedCards.push_back(cardNum + cardType);
    return {cardNum, cardType};
}

void GameWidget::drawCard(Player* player, Card* temp, QLabel* labelCard, QLabel* labelScore, QPropertyAnimation* anim, int x, int y){


    QPixmap pix(temp->getPathToCardImg());
    labelCard -> setPixmap(pix.scaled(100, 170));

    anim->setDuration(1000);
    anim->setStartValue(QRect(680, 200, 100, 170));
    anim->setEndValue(QRect(x, y, 100, 170));
    anim->start();

    // change score
    if (temp->getIsBackSide()){
        player->setAmountOfPoints(0);
        player->setAmountOfBackPoints(temp->giveNumOfPointsForCard(player->getAmountOfPoints()));
    }
    else{
        player->setAmountOfPoints(temp->giveNumOfPointsForCard(player->getAmountOfPoints()));
    }

    labelScore->setText(QString::number(player->getAmountOfPoints()));
    soundPlayer("qrc:/sound/Assets/sound/flipCard.mp3");
}

void GameWidget::timer(int time = 900){
    QTimer timer;
    timer.setInterval(time);
    QEventLoop loop;
    connect(&timer, SIGNAL(timeout()), &loop, SLOT(quit()));
    timer.start();
    loop.exec();
}

void GameWidget::dealerMove(){
    QPixmap pix(dealer.getPathToBackCardImg());
    ui->labelDealer1 -> setPixmap(pix.scaled(100, 170));

    dealer.setAmountOfPoints(dealer.getAmountOfBackPoints());
    ui->labelDealerScore->setText(QString::number(dealer.getAmountOfPoints()));

    timer();

    int playerScore = user.getAmountOfPoints();
    int dealerScore = dealer.getAmountOfPoints();

    int iterations = 1;

    while(dealerScore < playerScore && iterations <= 4){

        Card card(randomCardGenerator(), pathForFrontImg);
        QLabel* label;
        QPropertyAnimation* animation;
        int x;

        switch(iterations){
            case 1:
                label = ui->labelDealer3;
                animation = animation23;
                x = 240;
                break;
            case 2:
                label = ui->labelDealer4;
                animation = animation24;
                x = 350;
                break;
            case 3:
                label = ui->labelDealer5;
                animation = animation25;
                x = 460;
                break;
            case 4:
                label = ui->labelDealer6;
                animation = animation26;
                x = 570;
                break;
        }

        drawCard(&dealer, &card, label, ui->labelDealerScore, animation, x, 20);
        dealerScore = dealer.getAmountOfPoints();
        iterations++;
        timer();
    }

    if (dealerScore > playerScore && dealerScore > 21){
        gameOver("You WIN");
    }
    else if (dealerScore > playerScore && dealerScore <= 21){
        gameOver("You Lose");
    }
    else if (dealerScore == playerScore){
        gameOver("Draw");
    }
}

void GameWidget::gameOver(QString text){

    if(text == "You WIN"){
        user.setAmountOfMoney(user.getPlayerBet());
    }
    else if (text == "You Lose"){
        user.setAmountOfMoney(user.getPlayerBet() * -1);
    }
    QMessageBox msgBox1;
    QPushButton *connectButton = msgBox1.addButton(tr("Play again"), QMessageBox::ActionRole);
    QPushButton *exitButton = msgBox1.addButton(tr("Exit"), QMessageBox::ActionRole);
    msgBox1.setWindowTitle("Information");
    msgBox1.setText(text);
    msgBox1.setInformativeText("Your bank now is: " + QString::number(user.getAmountOfMoney()));
    msgBox1.exec();

    if (msgBox1.clickedButton() == connectButton) {
        backgroundMusic->setSource(QUrl::fromLocalFile("qrc:/sound/Assets/sound/game-setting-fantasy.mp3"));
        backgroundMusic->play();
        startGame();
    }
    else if (msgBox1.clickedButton() == exitButton) {
        QCoreApplication::quit();
    }
}

void GameWidget::checkListCardFrontTypes(){
    listCardFrontTypes.clear();
    QString path = QDir::currentPath() + "/Assets/";

    QDir directory(path);

    // Get a list of all the folders in the directory
    QStringList folders = directory.entryList(QDir::Dirs | QDir::NoDotAndDotDot);

    // Add the folder names to the list
    foreach (QString folder, folders)
    {
        if(folder != "back")
            listCardFrontTypes.append(folder);
    }
}

void GameWidget::checkListCardBackTypes(){
    listCardBackTypes.clear();

    QDir directory(QDir::currentPath() + "/Assets/back/");

    directory.setFilter(QDir::Files);
    QFileInfoList list = directory.entryInfoList();

    for (int i = 0; i < list.size(); i++) {
        QFileInfo fileInfo = list.at(i);
        QString fileName = fileInfo.fileName();
        listCardBackTypes.append(fileName);
    }
}

void GameWidget::messageInfo(QString title, QString text, QString informativeText){
    msgBox.setIcon(QMessageBox::Information);
    msgBox.setWindowTitle(title);
    msgBox.setText(text);
    msgBox.setInformativeText(informativeText);
    msgBox.exec();
}

// Buttons
void GameWidget::on_btnStand_clicked()
{
    soundPlayer("qrc:/sound/Assets/sound/clickButton.mp3");
    ui->btnHit->setEnabled(false);
    ui->btnStand->setEnabled(false);

    dealerMove();
}


void GameWidget::on_btnHit_clicked()
{
    soundPlayer("qrc:/sound/Assets/sound/clickButton.mp3");

    // Draw cards for each click on HIT btn
    Card card(randomCardGenerator(), pathForFrontImg);
    switch(countOfPressHit){
        case 1:
            drawCard(&user, &card, ui->labelPlayer3, ui->labelPlayerScore, animation3, 240, 380);
            break;
        case 2:
            drawCard(&user, &card, ui->labelPlayer4, ui->labelPlayerScore, animation4, 350, 380);
            break;
        case 3:
            drawCard(&user, &card, ui->labelPlayer5, ui->labelPlayerScore, animation5, 460, 380);
            break;
        case 4:
            drawCard(&user, &card, ui->labelPlayer6, ui->labelPlayerScore, animation6, 570, 380);
            break;
    }

    countOfPressHit++;
    if (user.checkLose()){
        gameOver("You Lose");
    }
}


void GameWidget::on_btnAddNewSkins_clicked()
{

    QMessageBox msgBox2;
    QPushButton *connectButton = msgBox2.addButton(tr("Front img"), QMessageBox::ActionRole);
    QPushButton *exitButton = msgBox2.addButton(tr("Back img"), QMessageBox::ActionRole);
    msgBox2.setWindowTitle("Make choose");
    msgBox2.setText("Choose which type of images you watn to add:");
    msgBox2.exec();

    if (msgBox2.clickedButton() == connectButton) {
        frontOrBack = true;
        QString infoText = "Your cards must be in .png format\n "
                           " 2_of_clubs\n 2_of_diamonds\n 2_of_hearts\n 2_of_spades\n 3_of_clubs\n\t...\n\n"
                           " Jack = 11\n Queen = 12\n King = 13\n Ace = 14\n\n"
                           "So, if we need King of diamonds,\nwe rename our file to 13_of_diamonds, and so on";
        messageInfo("Important", "This is examples, how you should name you files.", infoText);
    }
    else if (msgBox2.clickedButton() == exitButton) {
        frontOrBack = false;
    }




    checkListCardFrontTypes();

    int maxCardFolder = listCardFrontTypes.size();
    QString creatingFolder;
    if(frontOrBack) creatingFolder = "png" + QString::number(maxCardFolder+1) + "/";
    else            creatingFolder = "back/";

    // Create a file dialog to let the user select the image files
    QStringList imageFiles = QFileDialog::getOpenFileNames(this, tr("Select Images"), QString(), tr("Image Files (*.png)"));

    // Get the path of the directory where you want to save the images
    QString saveDirectory = QDir::currentPath() + "/Assets/" + creatingFolder;

    if(!imageFiles.isEmpty()){
        // Create the directory if it doesn't exist
        QDir().mkpath(saveDirectory);

        // Copy the selected files to the save directory
        foreach(QString imagePath, imageFiles)
        {
            // Get the filename of the image
            QString imageName = QFileInfo(imagePath).fileName();

            // Create a QFile object for the image file
            QFile imageFile(imagePath);

            // Set the path for the output file
            QString savePath = saveDirectory + imageName;

            // Create a QFile object for the output file
            QFile outputFile(savePath);

            // Open the image file for reading
            if (imageFile.open(QIODevice::ReadOnly))
            {
                // Open the output file for writing
                if (outputFile.open(QIODevice::WriteOnly))
                {
                    // Copy the image data to the output file
                    outputFile.write(imageFile.readAll());

                    // Close the output file
                    outputFile.close();
                }

                // Close the image file
                imageFile.close();
            }
        }
    }
}


void GameWidget::on_btnMute_clicked()
{
    isMuted = !isMuted;
    audioOutput1->setMuted(isMuted);
    audioOutput->setMuted(isMuted);

    QPixmap pixmapMute(":/icons/Assets/soundUnmute.png");
    QPixmap pixmapUnMute(":/icons/Assets/soundMute.png");
    QIcon ButtonIconMute(pixmapMute);
    QIcon ButtonIconUnMute(pixmapUnMute);

    if(!isMuted) ui->btnMute->setIcon(ButtonIconMute);
    else    ui->btnMute->setIcon(ButtonIconUnMute);
    ui->btnMute->setIconSize(QSize(35, 35));
}


void GameWidget::changeBack()
{
    checkListCardBackTypes();
    bool ok;

    QString item = QInputDialog::getItem(this, tr("Choose back img"),
                                        tr("Card Types:"), listCardBackTypes, 0, false, &ok);

    if (ok && !item.isEmpty()){
        updatedPathForBackImg = "back/" + item;

        messageInfo("Important", "Changes will take effect with a new game.", "");
    }
}


void GameWidget::changeFront()
{
    checkListCardFrontTypes();
    bool ok;

    QString item = QInputDialog::getItem(this, tr("Choose front img"),
                                        tr("Card Types:"), listCardFrontTypes, 0, false, &ok);

    if (ok && !item.isEmpty()){
        updatedPathForFrontImg = "png" + QString::number(listCardFrontTypes.indexOf(item)+1);

        messageInfo("Important", "Changes will take effect with a new game.", "");
    }
}


void GameWidget::on_btnChangeImg_clicked()
{
    QMessageBox msgBox3;
    QPushButton *connectButton = msgBox3.addButton(tr("Front img"), QMessageBox::ActionRole);
    QPushButton *exitButton = msgBox3.addButton(tr("Back img"), QMessageBox::ActionRole);
    msgBox3.setWindowTitle("Make choose");
    msgBox3.setText("Choose which type of images you watn to change:");
    msgBox3.exec();

    if (msgBox3.clickedButton() == connectButton) {
        changeFront();
    }
    else if (msgBox3.clickedButton() == exitButton) {
        changeBack();
    }
}

