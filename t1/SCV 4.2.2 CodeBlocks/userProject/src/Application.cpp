#include "Application.h"

Application::Application(void) : Kernel()
{
    setWindowSize(500, 500);
    lockWindowSize(false);
    setFramesPerSecond(60);

    setWindowTitle("SCV v4.2 - Interface Designer");
}

Application::~Application(void)
{
}

void Application::init(void)
{
    _mainPanel = new scv::Panel(scv::Point(2, 2), scv::Point(2, 2));
    scv::Button *button0_scv_button = new scv::Button(scv::Point(0, 0), "SCV Button");
    _mainPanel->addChild(button0_scv_button);
    scv::Button *button1_scv_button = new scv::Button(scv::Point(0, 0), "SCV Button");
    _mainPanel->addChild(button1_scv_button);
    scv::GroupLayout *layout = new scv::GroupLayout(_mainPanel);
    _mainPanel->setLayout(layout);

    layout->setHorizontalGroup(
        scv::GroupLayout::createParallelGroup()
        ->addGroup(scv::GroupLayout::createParallelGroup()
                   ->addComponent(button0_scv_button)
                   ->addComponent(button1_scv_button)
                  )
    );
    layout->setVerticalGroup(
        scv::GroupLayout::createParallelGroup()
        ->addGroup(scv::GroupLayout::createSequentialGroup()->setAutoCreateGaps(true)
                   ->addComponent(button0_scv_button)
                   ->addComponent(button1_scv_button)
                  )
    );


    addComponent(_mainPanel);
}

void Application::onMouseClick(const scv::MouseEvent &evt)
{
}
void Application::onMouseHold(const scv::MouseEvent &evt)
{
}
void Application::onMouseOver(const scv::MouseEvent &evt)
{
}
void Application::onMouseUp(const scv::MouseEvent &evt)
{
}
void Application::onMouseWheel(const scv::MouseEvent &evt)
{
}

void Application::onKeyPressed(const scv::KeyEvent &evt)
{
}
void Application::onKeyUp(const scv::KeyEvent &evt)
{
}

void Application::onSizeChange(void)
{
    _mainPanel->setSize(getWidth() - 4, getHeight() - 4);
}
void Application::onPositionChange(void)
{
}
