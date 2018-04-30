#include "..\DirectUI\DirectUI.h"
#include <string>

using namespace DirectUI;


struct Person : DependencyObject {
    DECLARE_DP(Person, Name, std::wstring);
    DECLARE_DP(Person, Age, int);

    void ModifyAge() {
        Age(Age() + 1);
    }
};

DEFINE_DP(Person, Name, std::wstring, L"Bart");
DEFINE_DP(Person, Age, int, 10);

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, LPWSTR lpCmdLine, int) {
    Application app;
    app.Initialize();

    Person p;

    auto nameTB = Create<TextBlock>();
    nameTB->BindTo(TextBlock::TextProperty, p, Person::NameProperty);
    nameTB->Text(L"Hello")->Foreground(Brushes::Yellow())->FontSize(30);

    auto button = Create<Button>();
    auto buttonText = Create<TextBlock>();
    buttonText->Text(L"Click me!");
    button->CornerRadius(DX::SizeF(5, 5))->Content(buttonText)->Padding(4)->FontSize(40)->Background(Brushes::Cyan())->Width(100)->Height(40);
    button->AddEventHandler(Button::ClickEvent, [nameTB, &p](auto& source, const auto& args) {
        nameTB->Text(L"Cactus");
        return true;
    });

    auto stack = Create<StackLayout>({ nameTB, button });

    Window window(L"Simple Data Binding");
    window.Content(stack);

    app.Run();
}
