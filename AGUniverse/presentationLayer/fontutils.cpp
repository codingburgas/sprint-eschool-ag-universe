#include "fontutils.h"

void setCustomFontAura(QWidget* widget, int fontSize) {
    int fontIdAura = QFontDatabase::addApplicationFont(":/assets/fonts/Aura Regular.ttf");

    QString familyAura = QFontDatabase::applicationFontFamilies(fontIdAura).at(0);
    QFont customFontAura(familyAura, fontSize);
    widget->setFont(customFontAura);
}

void setCustomFontCT(QWidget* widget, int fontSize) {
    int fontIdCT = QFontDatabase::addApplicationFont(":/assets/fonts/CrimsonText-SemiBold.ttf");

    QString familyCT = QFontDatabase::applicationFontFamilies(fontIdCT).at(0);
    QFont customFontCT(familyCT, fontSize);
    widget->setFont(customFontCT);
}
void setCustomFontAllerta(QWidget* widget, int fontSize) {
    int fontIdAllerta = QFontDatabase::addApplicationFont(":/assets/fonts/Allerta-Regular.ttf");

    QString familyAllerta = QFontDatabase::applicationFontFamilies(fontIdAllerta).at(0);
    QFont customFontAllerta(familyAllerta, fontSize);
    widget->setFont(customFontAllerta);
}
