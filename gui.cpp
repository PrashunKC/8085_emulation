#include <QApplication>
#include <QMainWindow>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTextEdit>
#include <QPushButton>
#include <QLabel>
#include <QTableWidget>
#include <QHeaderView>
#include <QGroupBox>
#include <QTimer>
#include <QFont>
#include "cpu8085.h"

class Emulator8085Window : public QMainWindow {
    Q_OBJECT

public:
    Emulator8085Window(QWidget *parent = nullptr) : QMainWindow(parent) {
        setWindowTitle("8085 Microprocessor Emulator");
        setMinimumSize(1000, 700);
        
        cpu = new CPU8085();
        
        // Central widget
        QWidget *centralWidget = new QWidget(this);
        setCentralWidget(centralWidget);
        
        QHBoxLayout *mainLayout = new QHBoxLayout(centralWidget);
        
        // Left panel - Registers and Controls
        QVBoxLayout *leftLayout = new QVBoxLayout();
        
        // Register display
        QGroupBox *registerGroup = new QGroupBox("Registers");
        QVBoxLayout *registerLayout = new QVBoxLayout();
        registerDisplay = new QTextEdit();
        registerDisplay->setReadOnly(true);
        registerDisplay->setMinimumHeight(100);
        registerDisplay->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        registerDisplay->setFont(QFont("Monospace", 11));
        registerDisplay->setLineWrapMode(QTextEdit::NoWrap);
        registerLayout->addWidget(registerDisplay);
        registerGroup->setLayout(registerLayout);
        leftLayout->addWidget(registerGroup, 3); // Give it weight for scaling
        
        // Flags display
        QGroupBox *flagsGroup = new QGroupBox("Flags");
        QVBoxLayout *flagsLayout = new QVBoxLayout();
        flagsDisplay = new QTextEdit();
        flagsDisplay->setReadOnly(true);
        flagsDisplay->setMinimumHeight(40);
        flagsDisplay->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        flagsDisplay->setFont(QFont("Monospace", 11));
        flagsDisplay->setLineWrapMode(QTextEdit::NoWrap);
        flagsLayout->addWidget(flagsDisplay);
        flagsGroup->setLayout(flagsLayout);
        leftLayout->addWidget(flagsGroup, 1); // Give it weight for scaling
        
        // Output display
        QGroupBox *outputGroup = new QGroupBox("Program Output");
        QVBoxLayout *outputLayout = new QVBoxLayout();
        outputDisplay = new QTextEdit();
        outputDisplay->setReadOnly(true);
        outputDisplay->setMinimumHeight(60);
        outputDisplay->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        outputDisplay->setFont(QFont("Monospace", 11));
        outputDisplay->setLineWrapMode(QTextEdit::NoWrap);
        outputDisplay->setPlaceholderText("Program results will appear here...");
        outputLayout->addWidget(outputDisplay);
        outputGroup->setLayout(outputLayout);
        leftLayout->addWidget(outputGroup, 2); // Give it weight for scaling
        
        // Control buttons
        QGroupBox *controlGroup = new QGroupBox("Controls");
        QVBoxLayout *controlLayout = new QVBoxLayout();
        
        QPushButton *resetBtn = new QPushButton("Reset");
        QPushButton *stepBtn = new QPushButton("Step");
        QPushButton *runBtn = new QPushButton("Run");
        QPushButton *stopBtn = new QPushButton("Stop");
        QPushButton *loadBtn = new QPushButton("Load Program");
        
        connect(resetBtn, &QPushButton::clicked, this, &Emulator8085Window::onReset);
        connect(stepBtn, &QPushButton::clicked, this, &Emulator8085Window::onStep);
        connect(runBtn, &QPushButton::clicked, this, &Emulator8085Window::onRun);
        connect(stopBtn, &QPushButton::clicked, this, &Emulator8085Window::onStop);
        connect(loadBtn, &QPushButton::clicked, this, &Emulator8085Window::onLoadProgram);
        
        // Set minimum button heights for better visibility
        resetBtn->setMinimumHeight(35);
        stepBtn->setMinimumHeight(35);
        runBtn->setMinimumHeight(35);
        stopBtn->setMinimumHeight(35);
        loadBtn->setMinimumHeight(35);
        
        controlLayout->addWidget(resetBtn);
        controlLayout->addWidget(stepBtn);
        controlLayout->addWidget(runBtn);
        controlLayout->addWidget(stopBtn);
        controlLayout->addWidget(loadBtn);
        controlLayout->addStretch();
        
        controlGroup->setLayout(controlLayout);
        controlGroup->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        leftLayout->addWidget(controlGroup, 2); // Give it weight for scaling
        
        mainLayout->addLayout(leftLayout, 1);
        
        // Right panel - Memory view
        QVBoxLayout *rightLayout = new QVBoxLayout();
        
        QGroupBox *memoryGroup = new QGroupBox("Memory (First 256 bytes)");
        QVBoxLayout *memoryLayout = new QVBoxLayout();
        
        memoryTable = new QTableWidget(16, 17);
        memoryTable->setFont(QFont("Monospace", 10));
        memoryTable->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        memoryTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        memoryTable->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        memoryTable->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        memoryTable->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        
        // Set headers
        QStringList headers;
        headers << "Addr";
        for (int i = 0; i < 16; i++) {
            headers << QString("%1").arg(i, 1, 16).toUpper();
        }
        memoryTable->setHorizontalHeaderLabels(headers);
        memoryTable->verticalHeader()->setVisible(false);
        
        memoryLayout->addWidget(memoryTable);
        memoryGroup->setLayout(memoryLayout);
        memoryGroup->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        rightLayout->addWidget(memoryGroup);
        
        // Status bar
        statusLabel = new QLabel("Status: Ready");
        rightLayout->addWidget(statusLabel);
        
        mainLayout->addLayout(rightLayout, 2);
        
        // Timer for run mode
        runTimer = new QTimer(this);
        connect(runTimer, &QTimer::timeout, this, &Emulator8085Window::onTimerStep);
        
        // Initial update
        updateDisplay();
    }
    
    ~Emulator8085Window() {
        delete cpu;
    }

private slots:
    void onReset() {
        cpu->reset();
        updateDisplay();
        statusLabel->setText("Status: Reset");
    }
    
    void onStep() {
        if (!cpu->halted) {
            cpu->step();
            updateDisplay();
            statusLabel->setText("Status: Stepped");
        } else {
            statusLabel->setText("Status: CPU Halted");
        }
    }
    
    void onRun() {
        if (!cpu->halted) {
            runTimer->start(100); // Execute step every 100ms
            statusLabel->setText("Status: Running...");
        }
    }
    
    void onStop() {
        runTimer->stop();
        statusLabel->setText("Status: Stopped");
    }
    
    void onTimerStep() {
        if (!cpu->halted) {
            cpu->step();
            updateDisplay();
        } else {
            runTimer->stop();
            statusLabel->setText("Status: CPU Halted");
        }
    }
    
    void onLoadProgram() {
        // Sample program: Add two numbers and store in C
        // MVI A, 05h  ; Load 5 into A
        // MVI B, 03h  ; Load 3 into B
        // ADD B       ; Add B to A (result: A = 8)
        // MOV C, A    ; Copy result to C
        // HLT         ; Halt
        uint8_t program[] = {
            0x3E, 0x05,  // MVI A, 05h
            0x06, 0x03,  // MVI B, 03h
            0x80,        // ADD B
            0x4F,        // MOV C, A
            0x76         // HLT
        };
        
        cpu->reset();
        cpu->loadProgram(program, sizeof(program), 0x0000);
        updateDisplay();
        statusLabel->setText("Status: Sample program loaded (Add 5 + 3, result in A and C)");
    }
    
    void updateDisplay() {
        // Update registers
        registerDisplay->setText(QString::fromStdString(cpu->getRegisterState()));
        
        // Update flags
        flagsDisplay->setText(QString::fromStdString(cpu->getFlagsState()));
        
        // Update output display with result information
        QString output;
        output += QString("Accumulator (A): %1 (0x%2, %3d)\n")
            .arg(QString::number(cpu->A, 2).rightJustified(8, '0'))
            .arg(cpu->A, 2, 16, QChar('0')).toUpper()
            .arg(cpu->A);
        output += QString("B Register: %1 (0x%2, %3d)\n")
            .arg(QString::number(cpu->B, 2).rightJustified(8, '0'))
            .arg(cpu->B, 2, 16, QChar('0')).toUpper()
            .arg(cpu->B);
        output += QString("C Register: %1 (0x%2, %3d)\n")
            .arg(QString::number(cpu->C, 2).rightJustified(8, '0'))
            .arg(cpu->C, 2, 16, QChar('0')).toUpper()
            .arg(cpu->C);
        output += QString("\nProgram Counter: 0x%1\n")
            .arg(cpu->PC, 4, 16, QChar('0')).toUpper();
        output += QString("Stack Pointer: 0x%1\n")
            .arg(cpu->SP, 4, 16, QChar('0')).toUpper();
        output += QString("Status: %1")
            .arg(cpu->halted ? "HALTED" : "RUNNING");
        
        outputDisplay->setText(output);
        
        // Update memory table (first 256 bytes)
        for (int row = 0; row < 16; row++) {
            // Address column
            uint16_t baseAddr = row * 16;
            QTableWidgetItem *addrItem = new QTableWidgetItem(
                QString("%1").arg(baseAddr, 4, 16, QChar('0')).toUpper()
            );
            addrItem->setForeground(Qt::black);
            addrItem->setBackground(QColor(230, 230, 230));
            memoryTable->setItem(row, 0, addrItem);
            
            // Memory values
            for (int col = 0; col < 16; col++) {
                uint16_t addr = baseAddr + col;
                uint8_t value = cpu->getMemory(addr);
                QTableWidgetItem *item = new QTableWidgetItem(
                    QString("%1").arg(value, 2, 16, QChar('0')).toUpper()
                );
                
                // Set text color to black for visibility
                item->setForeground(Qt::black);
                
                // Highlight current PC location
                if (addr == cpu->PC) {
                    item->setBackground(Qt::yellow);
                } else {
                    item->setBackground(Qt::white);
                }
                
                memoryTable->setItem(row, col + 1, item);
            }
        }
    }

private:
    CPU8085 *cpu;
    QTextEdit *registerDisplay;
    QTextEdit *flagsDisplay;
    QTextEdit *outputDisplay;
    QTableWidget *memoryTable;
    QLabel *statusLabel;
    QTimer *runTimer;
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    
    Emulator8085Window window;
    window.show();
    
    return app.exec();
}

#include "gui.moc.cpp"
