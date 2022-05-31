#include <QtWidgets/QApplication>
#include <QPushButton>
#include <QPixmap>
#include <QPainter>
#include <QPaintEvent>
#include <QTimer>
#include <QMediaPlayer>

class ImageButton : public QPushButton
{
    Q_OBJECT

public:
    ImageButton() = default;
    ImageButton(QWidget* parent);
    void paintEvent(QPaintEvent* event) override;
    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;
    void keyPressEvent(QKeyEvent* event) override;

public slots:
    void setUp();
    void setDown();

private:
    QPixmap mCurrentButtonPixmap;
    QPixmap mButtonDownPixmap;
    QPixmap mButtonUpPixmap;
    bool isDown = false;
};

ImageButton::ImageButton(QWidget* parent)
{
    setParent(parent);
    setToolTip("Stop");
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    mButtonUpPixmap = QPixmap("C:\\Projects\\Qt\\testProgram\\openButton.png");
    mButtonDownPixmap = QPixmap("C:\\Projects\\Qt\\testProgram\\closeButton.png");
    mCurrentButtonPixmap = mButtonUpPixmap;
    setGeometry(mCurrentButtonPixmap.rect());

    auto* player = new QMediaPlayer;
    player->setMedia(QUrl::fromLocalFile("C:\\Projects\\Qt\\testProgram\\clickButton.mp3"));
    player->setVolume(75);

    connect(this, &QPushButton::clicked, [this, player]() 
        {
            player->play();
            setDown();
        });
}

void ImageButton::paintEvent(QPaintEvent* event)
{
    QPainter p(this);
    p.drawPixmap(event->rect(), mCurrentButtonPixmap);
}

QSize ImageButton::sizeHint() const
{
    return QSize(100, 100);
}

QSize ImageButton::minimumSizeHint() const
{
    return sizeHint();
}

void ImageButton::keyPressEvent(QKeyEvent* event)
{
    setDown();
}

void ImageButton::setDown()
{
    mCurrentButtonPixmap = mButtonDownPixmap;
    update();

    QTimer::singleShot(300, this, &ImageButton::setUp);
}

void ImageButton::setUp()
{
    mCurrentButtonPixmap = mButtonUpPixmap;
    update();
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    ImageButton redButton(nullptr);
    redButton.setFixedSize(100, 100);
    redButton.move(1000, 400);
    redButton.show();

    return a.exec();
}

#include <main.moc>