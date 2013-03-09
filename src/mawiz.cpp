/*
 *  MaWiz - Manjaro Wizard Library
 *  Roland Singer <roland@manjaro.org>
 *
 *  Copyright (C) 2007 Free Software Foundation, Inc.
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "mawiz.h"
#include "mawiz_p.h"
#include "ui_mawiz.h"


//###
//### MaWiz - Public
//###


MaWiz::MaWiz() :
    QMainWindow(),
    pData(new MaWiz_P(this))
{
    // Basic window setup
    // We can't set the Qt::WA_TranslucentBackground attribute here, due to the changes in Qt5. Qt::WA_TranslucentBackground has to be set before ui.setupUI is called.
    setMaximumSize(784, 584);
    setMinimumSize(784, 584);

    // Center window on the screen
    setGeometry(
        QStyle::alignedRect(
            Qt::LeftToRight,
            Qt::AlignCenter,
            size(),
            qApp->desktop()->availableGeometry()
        ));

    // Set up Signals and Slots
    connect(pData->ui->buttonQuit, SIGNAL(clicked())    ,   this, SIGNAL(quitRequested()));
    connect(&pData->stackedWidget, SIGNAL(currentChanged(int))  ,   this, SIGNAL(currentPageChanged(int)));
}



MaWiz::~MaWiz()
{
    delete pData;
}



void MaWiz::setButtonQuitText(QString text) {
    pData->ui->buttonQuit->setText(text);
}



void MaWiz::setButtonHelpText(QString text) {
    pData->ui->buttonHelp->setText(text);
}



void MaWiz::setButtonReturnText(QString text) {
    pData->ui->buttonReturn->setText(text);
}



void MaWiz::setButtonBackText(QString text) {
    pData->ui->buttonBack->setText(text);
}



void MaWiz::setButtonForwardText(QString text) {
    pData->ui->buttonForward->setText(text);
}



void MaWiz::setButtonQuitVisible(bool visible) {
    pData->ui->buttonQuit->setVisible(visible);
}



void MaWiz::setButtonBackVisible(bool visible) {
    pData->ui->buttonBack->setVisible(visible);
}



void MaWiz::setButtonForwardVisible(bool visible) {
    pData->ui->buttonForward->setVisible(visible);
}



void MaWiz::setButtonQuitEnabled(bool enabled) {
    pData->ui->buttonQuit->setEnabled(enabled);
}



void MaWiz::setButtonBackEnabled(bool enabled) {
    pData->ui->buttonBack->setEnabled(enabled);
}



void MaWiz::setButtonForwardEnabled(bool enabled) {
    pData->ui->buttonForward->setEnabled(enabled);
}



void MaWiz::setLabelTitleText(QString text) {
    pData->ui->labelTitle->setText(text);
}



void MaWiz::setHelpTitle(QString title) {
    pData->helpTitle = title;
}



void MaWiz::setWindowMovingEnabled(bool enabled) {
    pData->moveBar.setMovingEnabled(enabled);
}



void MaWiz::setProgressBarVisible(bool visible) {
    pData->ui->progressBar->setVisible(visible);
}



void MaWiz::setProgressBarMaximumValue(int value) {
    pData->ui->progressBar->setMaximum(value);
}



void MaWiz::setProgressBarValue(int value) {
    pData->ui->progressBar->setValue(value);
}



void MaWiz::setProgressBarText(QString text, bool showProgress) {
    if (showProgress)
        text = text.trimmed() + "  -  %p%";

    pData->ui->progressBar->setFormat(text);
}



int MaWiz::addPage(MaWizPage* page) {
    int index;

    page->setParent(&pData->stackedWidget);
    index = pData->stackedWidget.addWidget(page);
    connect(page, SIGNAL(checkReady())  ,   pData, SLOT(checkCurrentPage()));

    pData->checkCurrentPage();
    return index;
}



void MaWiz::setCurrentPage(int index) {
    pData->stackedWidget.setCurrentIndex(index);
}



int MaWiz::currentPageIndex() {
    return pData->stackedWidget.currentIndex();
}



bool MaWiz::isFirstPage() {
    return (pData->stackedWidget.currentIndex() <= 0);
}



bool MaWiz::isLastPage() {
    return (pData->stackedWidget.currentIndex() >= pData->stackedWidget.count() - 1);
}



void MaWiz::show() {
    pData->currentPageChanged();

    QMainWindow::show();
}



//###
//### MaWiz - Private
//###



void MaWiz::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.drawImage(0, 0, QImage(":/images/resources/main_frame_border.png").scaled(size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    painter.end();
}




//###
//### MaWiz_P - Public
//###



MaWiz_P::MaWiz_P(QMainWindow *parent) :
    QObject(),
    ui(new Ui::MaWiz),
    moveBar(parent)
{
    // Save parent pointer
    this->parent = parent;

    // Qt::WA_TranslucentBackground has to be set before ui.setupUI is called.
    parent->setWindowFlags(parent->windowFlags() | Qt::FramelessWindowHint);
    parent->setAttribute(Qt::WA_TranslucentBackground);

    // Draw children
    ui->setupUi(parent);

    // Hide progressbar, help button and return button area
    ui->progressBar->setVisible(false);
    ui->buttonHelp->setVisible(false);
    ui->returnButtonArea->setVisible(false);

    // Setup moveBar
    moveBar.setMaximumHeight(35);
    moveBar.setMinimumHeight(35);
    ui->mainLayout->insertWidget(0, &moveBar);

    // Setup stacked widget
    pageHelpIndex = ui->stackedWidget->currentIndex();
    pageStackedWidgetIndex = ui->stackedWidget->addWidget(&stackedWidget);
    ui->stackedWidget->setCurrentIndex(pageStackedWidgetIndex);
    ui->stackedWidget->setAutoFillBackground(true);

    // Connect Signals and Slots
    connect(&stackedWidget, SIGNAL(currentChanged(int))  ,   this, SLOT(currentPageChanged()));
    connect(ui->buttonBack, SIGNAL(clicked())   ,   this, SLOT(setPreviousPage()));
    connect(ui->buttonForward, SIGNAL(clicked())    ,   this, SLOT(setNextPage()));
    connect(ui->buttonHelp, SIGNAL(clicked())   ,   this, SLOT(buttonHelp_clicked()));
    connect(ui->buttonReturn, SIGNAL(clicked()) ,   this, SLOT(buttonReturn_clicked()));
}



MaWiz_P::~MaWiz_P()
{
    // Page deletion should be managed by the app!

    // Delete UI
    delete ui;
}



void MaWiz_P::setNextPage() {
    stackedWidget.setCurrentIndex(stackedWidget.currentIndex() + 1);
}



void MaWiz_P::setPreviousPage() {
    stackedWidget.setCurrentIndex(stackedWidget.currentIndex() - 1);
}



void MaWiz_P::currentPageChanged() {
    // First set the buttons
    checkCurrentPage();

    MaWizPage *currentPage = dynamic_cast<MaWizPage*>(stackedWidget.currentWidget());
    if (!currentPage)
        return;

    // Trigger virtual activated method
    currentPage->activated();

    ui->labelTitle->setText(currentPage->getTitle());

    if (!currentPage->getGoBack())
        ui->buttonBack->setEnabled(false);
    else
        ui->buttonBack->setEnabled(true);

    if (!currentPage->getHelpURL().isEmpty())
        ui->buttonHelp->setVisible(true);
    else
        ui->buttonHelp->setVisible(false);
}



void MaWiz_P::checkCurrentPage() {
    const int currentIndex = stackedWidget.currentIndex();
    const int pagesCount = stackedWidget.count();

    // Disable or enable buttons depending on index if page is ready
    if (currentIndex <= 0)
        ui->buttonBack->setVisible(false);
    else
        ui->buttonBack->setVisible(true);

    if (currentIndex >= pagesCount - 1)
        ui->buttonForward->setVisible(false);
    else
        ui->buttonForward->setVisible(true);

    MaWizPage *currentPage = dynamic_cast<MaWizPage*>(stackedWidget.currentWidget());

    if (currentPage && !currentPage->ready())
        ui->buttonForward->setEnabled(false);
    else
        ui->buttonForward->setEnabled(true);
}



void MaWiz_P::buttonHelp_clicked() {
    MaWizPage *currentPage = dynamic_cast<MaWizPage*>(stackedWidget.currentWidget());
    if (!currentPage)
        return;

    ui->labelTitle->setText(helpTitle);
    ui->webView->setUrl(currentPage->getHelpURL());
    ui->returnButtonArea->setVisible(true);
    ui->MainButtonArea->setVisible(false);
    ui->stackedWidget->setCurrentIndex(pageHelpIndex);
}



void MaWiz_P::buttonReturn_clicked() {
    ui->returnButtonArea->setVisible(false);
    ui->MainButtonArea->setVisible(true);
    ui->stackedWidget->setCurrentIndex(pageStackedWidgetIndex);
    currentPageChanged();
}

