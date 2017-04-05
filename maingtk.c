#include <stdlib.h>
#include <stdio.h>
#include <gtk/gtk.h>
#include <string.h>
#include "lib/libresistance/libresistance.h"
#include "lib/libpower/libpower.h"
#include "lib/libcomponent/libcomponent.h"
#include "electrolibui.h"

static GtkGrid* _mainGrid;
static char* _voltage = "0";
static char _connectionType = 'S';
static char* _numberOfComponents = "1";
static char** _resistanceValueList = NULL;

static void setResistanceItemValue(int index, char* value) {
    _resistanceValueList[index-1] = value;
}

static void resistanceListItemChanged (GtkEditable *editable,
               gpointer     user_data) {
    if(user_data != NULL){
        char* value = gtk_editable_get_chars(editable, 0,-1);
        printDebugText("Resistance value with index %d was set to: %s\n", user_data, value);
        setResistanceItemValue(user_data, value);
    }
}

static void setConnectionType(char connectionType) {
    _connectionType = connectionType;
    printDebugText("Connection type changed to %c", _connectionType);
}

static char getConnectionType() {
    return _connectionType;
}

static void setVoltage(char* value){
    printDebugText("Voltage changed from %s to %s", value, _voltage);
    _voltage = value;
}

static float getVoltage() {
    return atof(_voltage);
}

static int getNumberOfComponents(){
    return atof(_numberOfComponents);
}

static void setNumberOfComponents(char* value){
    int oldNumberOfComponents = getNumberOfComponents();
    _numberOfComponents = value;
    printDebugText("Number of components before change: %d, after: %s", oldNumberOfComponents, value);
    int i = 0;
    printDebugText("All values before changing the number of components:");
    if(_resistanceValueList == NULL)
        printDebugText("Resistance is null");
    while(i < oldNumberOfComponents){
        printDebugText("Checking positions..");
        printDebugText("Position: %d had %s \n", i, _resistanceValueList[i]);
        i = i + 1;
    }
    printDebugText("MainGrid address %p", _mainGrid);
    initResistanceListSection(getNumberOfComponents(), oldNumberOfComponents, &_resistanceValueList, _mainGrid, resistanceListItemChanged);
}

static float* getResistanceItems(){
    float* resistance = malloc(getNumberOfComponents()*sizeof(float));
    int i = 0;
    while(i < getNumberOfComponents()){
        resistance[i] = atof(_resistanceValueList[i]);
        printDebugText("Value converted from: %s to: %f", _resistanceValueList[i], resistance[i]);
        i = i + 1;
    }
    return resistance;
}

static void voltageChanged (GtkEditable *editable,
               gpointer     user_data) {
    setVoltage(gtk_editable_get_chars(editable, 0,-1));
}

static void connectionTypeChanged (GtkCheckButton* checkButton,
               gpointer     user_data) {
    gboolean isChecked = gtk_toggle_button_get_active (checkButton);
    if(isChecked == TRUE){
        printDebugText("Checked");
        setConnectionType('P');
    } else {
        setConnectionType('S');
    }
}

static void numberOfComponentsChanged (GtkComboBox* comboBox,
               gpointer     user_data) {
    setNumberOfComponents(gtk_combo_box_text_get_active_text (comboBox));
}

static gboolean delete_event(GtkWidget *widget,
                                GdkEvent *event,
                                gpointer data)
{
    printDebugText("delete event occured");
    return FALSE;
}

static void destroy(GtkWidget *widget,
                    gpointer data)
{
    gtk_main_quit();
}

void button_clicked(){
    int RESISTANCEOUTPUTLABELROW = 6;
    int VOLTAGEOUTPUTLABELROW = 7;
    int E12OUTPUTLABELROW = 8;
    float* replaceResistanceValues = calloc(3,sizeof(float));

    float totalresistance = calc_resistance(getNumberOfComponents(), getConnectionType(), getResistanceItems());
    float totalpower = calc_power_r(getVoltage(), totalresistance);
    int numberOfResistors = e_resistance(totalresistance, replaceResistanceValues);

    char formatedMessage[100];
    sprintf(formatedMessage, "Ersättningsresistance %.1f ohm", totalresistance);
    addOutputLabel(_mainGrid, formatedMessage, 1, RESISTANCEOUTPUTLABELROW, _mainGrid);
    sprintf(formatedMessage, "Effekt %.2f W", totalpower);
    addOutputLabel(_mainGrid, formatedMessage, 1, VOLTAGEOUTPUTLABELROW, _mainGrid);
    sprintf(formatedMessage, "Ersättningsresistans i E12-serien koppliade i serie: %.0f, %.0f, %.0f", *replaceResistanceValues, *(replaceResistanceValues+1), *(replaceResistanceValues+2));
    addOutputLabel(_mainGrid, formatedMessage, 1, E12OUTPUTLABELROW, _mainGrid);
}

int main(int argc, char *argv[]){
    GtkWidget *calcButton;
    GtkWidget *closeButton;
    //g_signal_connect_swapped(calcButton, "clicked", G_CALLBACK(gtk_widget_destroy), window);

    _mainGrid = createWindowAndMainGrid(argc, argv, destroy, delete_event);

    calcButton = gtk_button_new_with_label("Beräkna!");

    g_signal_connect(calcButton, "clicked", G_CALLBACK(button_clicked), NULL);
    
    addHeader("Ange basdata: ",_mainGrid, 1, 1);
    addInputSection("Ange spänningskälla i V: ",_mainGrid, voltageChanged, 1, 2,0);
    addCheckbox("Räkna med Parallell koppling istället för Seriell",_mainGrid, connectionTypeChanged, 1, 3);
    addDropDownList(10,_mainGrid, numberOfComponentsChanged, 1,4);
    
    addHeader("Komponenter och spänning: ",_mainGrid, 2, 1);
    initResistanceListSection(getNumberOfComponents(),0, &_resistanceValueList, _mainGrid, resistanceListItemChanged);
    
    gtk_grid_attach(_mainGrid, calcButton, 1, 5,2,1);
    gtk_widget_show(_mainGrid);
    gtk_widget_show(calcButton);

    gtk_main();
    return 0;
}