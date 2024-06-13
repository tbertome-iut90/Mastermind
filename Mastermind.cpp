#include <QApplication>
#include <QMainWindow>
#include <QWidget>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <vector>
#include <random>
#include <QMessageBox>

// red, yellow, green, blue, orange, purple
QStringList colors = {"#FF0000", "#FFFF00", "#00FF00", "#0000FF", "#FFA500", "#800080"};

class NumberPickerWidget : public QWidget {
public:
    NumberPickerWidget(QWidget *parent = nullptr) : QWidget(parent), attemptsLeft(12) {
        QVBoxLayout *layout = new QVBoxLayout;
        setLayout(layout);

        QGridLayout *attemptsLayout = new QGridLayout;
        layout->addLayout(attemptsLayout);

        for (int i = 0; i < MAX_ATTEMPTS; ++i) {
            std::vector<QPushButton *> row;
            for (int j = 0; j < 4; ++j) {
                QPushButton *button = new QPushButton("");
                button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
                button->setFixedSize(40, 40);
                attemptsLayout->addWidget(button, i, j);
                row.push_back(button);
            }
            // add button for good and good placement
            QPushButton *goodAndGoodPlacementButton = new QPushButton("");
            goodAndGoodPlacementButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            goodAndGoodPlacementButton->setFixedSize(20, 20);
            attemptsLayout->addWidget(goodAndGoodPlacementButton, i, 4);
            row.push_back(goodAndGoodPlacementButton);
            // set the color of the button to white
            goodAndGoodPlacementButton->setStyleSheet("background-color: white");

            // add button for good but wrong placement
            QPushButton *goodButWrongPlacementButton = new QPushButton("");
            goodButWrongPlacementButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            goodButWrongPlacementButton->setFixedSize(20, 20);
            attemptsLayout->addWidget(goodButWrongPlacementButton, i, 5);
            row.push_back(goodButWrongPlacementButton);
            // set the color of the button to red
            goodButWrongPlacementButton->setStyleSheet("background-color: red");

            attemptButtons.push_back(row);
        }

        QLabel *textLabel = new QLabel("Selected Numbers:");
        layout->addWidget(textLabel);

        QHBoxLayout *squaresLayout = new QHBoxLayout;
        layout->addLayout(squaresLayout);
        for (int i = 0; i < 4; ++i) {
            QPushButton *square = new QPushButton("");
            square->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            squaresLayout->addWidget(square);
            squares.push_back(square);
        }

        QGridLayout *gridLayout = new QGridLayout;
        layout->addLayout(gridLayout);
        std::vector<int> numbers = {1, 2, 3, 4, 5, 6};
        int row = 0, col = 0;
        for (int number : numbers) {
            QPushButton *button = new QPushButton();
            button->setStyleSheet(QString("background-color: %1").arg(colors[number - 1]));
            button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            button->setFixedSize(40, 40);
            gridLayout->addWidget(button, row, col);
            col++;
            if (col == 3) {
                col = 0;
                row++;
            }
            connect(button, &QPushButton::clicked, this, [this, number]() {
                updateCode(number);
            });
        }

        QPushButton *backspaceButton = new QPushButton("Backspace");
        layout->addWidget(backspaceButton);
        connect(backspaceButton, &QPushButton::clicked, this, &NumberPickerWidget::backspace);

        confirmButton = new QPushButton("Confirm");
        layout->addWidget(confirmButton);
        confirmButton->setEnabled(false);
        connect(confirmButton, &QPushButton::clicked, this, &NumberPickerWidget::confirmNumbers);

        generateSecretCombination();
    }

private:
    static const int MAX_ATTEMPTS = 12;
    std::vector<QPushButton *> squares;
    std::vector<std::vector<QPushButton *>> attemptButtons;
    std::vector<int> secretCombination;
    std::vector<int> selectedNumbers;
    QPushButton *confirmButton;
    int attemptsLeft;

    void updateCode(int number) {
        if (selectedNumbers.size() < 4) {
            selectedNumbers.push_back(number);
            squares[selectedNumbers.size() - 1]->setStyleSheet(QString("background-color: %1").arg(colors[number - 1]));
            if (selectedNumbers.size() == 4) {
                confirmButton->setEnabled(true);
            }
        }
    }

    void backspace() {
        if (!selectedNumbers.empty()) {
            selectedNumbers.pop_back();
            squares[selectedNumbers.size()]->setStyleSheet("");
            confirmButton->setEnabled(false);
        }
    }

    void confirmNumbers() {
        attemptsLeft--;

        int row = MAX_ATTEMPTS - attemptsLeft - 1;
        for (int i = 0; i < 4; ++i) {
            attemptButtons[row][i]->setStyleSheet(QString("background-color: %1").arg(colors[selectedNumbers[i] - 1]));
        }

        for (QPushButton *square : squares) {
            square->setStyleSheet("");
        }
        confirmButton->setEnabled(false);

        QString numbersText;
        for (int number : selectedNumbers) {
            numbersText += QString::number(number) + " ";
        }

        attemptButtons[row][4]->setText(QString::number(calculateGoodAndGoodPlacement()));
        attemptButtons[row][5]->setText(QString::number(calculateGoodButWrongPlacement()));

        bool correctGuess = true;
        for (int i = 0; i < 4; ++i) {
            if (selectedNumbers[i] != secretCombination[i]) {
                correctGuess = false;
                break;
            }
        }

        selectedNumbers.clear();

        if (correctGuess) {
            QMessageBox::information(this, "Mastermind", "Congratulations! You guessed the secret combination.");
            resetGame();
        } else {
            if (attemptsLeft == 0) {
                QMessageBox::information(this, "Mastermind", "Game over! You've run out of attempts.");
                resetGame();
            } else {
            }
        }
    }

    void generateSecretCombination() {
        secretCombination.clear();
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(1, 6);
        for (int i = 0; i < 4; ++i) {
            secretCombination.push_back(dis(gen));
        }
    }

    void resetGame() {
        attemptsLeft = 12;
        generateSecretCombination();
        for (std::vector<QPushButton *> &row : attemptButtons) {
            for (QPushButton *button : row) {
                button->setStyleSheet("");
            }
            row[4]->setStyleSheet("background-color: white");
            row[4]->setText("");
            row[5]->setStyleSheet("background-color: red");
            row[5]->setText("");
        }
    }

    int calculateGoodAndGoodPlacement() {
        int goodAndGoodPlacement = 0;
        for (int i = 0; i < 4; ++i) {
            if (selectedNumbers[i] == secretCombination[i]) {
                goodAndGoodPlacement++;
            }
        }
        return goodAndGoodPlacement;
    }

    int calculateGoodButWrongPlacement() {
        int goodButWrongPlacement = 0;
        std::vector<int> secretCombinationCopy = secretCombination;
        std::vector<int> selectedNumbersCopy = selectedNumbers;

        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                if (selectedNumbersCopy[i] == secretCombinationCopy[j]) {
                    secretCombinationCopy[j] = 0;
                    break;
                }
            }
        }

        for (int i = 0; i < 4; ++i) {
            if (secretCombinationCopy[i] == 0) {
                goodButWrongPlacement++; 
            }
        }

        int goodAndGoodPlacement = 0;
        for (int i = 0; i < 4; ++i) {
            if (selectedNumbers[i] == secretCombination[i]) {
                goodAndGoodPlacement++;
            }
        }

        goodButWrongPlacement -= goodAndGoodPlacement;

        return goodButWrongPlacement;
    }
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QMainWindow mainWindow;
    mainWindow.setWindowTitle("Mastermind");
    mainWindow.resize(400, 800);

    NumberPickerWidget widget;
    mainWindow.setCentralWidget(&widget);

    mainWindow.show();

    return app.exec();
}
