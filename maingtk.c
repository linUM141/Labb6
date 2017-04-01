#include <stdlib.h>
#include <stdio.h>
#include <gtk/gtk.h>
#include <string.h>
#include "lib/libresistance/libresistance.h"
#include "lib/libpower/libpower.h"
#include "lib/libcomponent/libcomponent.h"

GtkGrid* _mainGrid;
char* _voltage = "0";
char* _connectionType = "S";
char* _numberOfComponents = "1";
char** _resistance;

/**
* @brief Prints a text with a given colour and a list of arguments
*
* A wrapper around printf that simplifies printing out test result text in different colours.
* @param text The text message to print out
* @param args The arguments for the text output, it's a va_list so provide it in the same way as for a printf call
* @return void
**/
static void printDebugText(const char* text, ...){   
    const char* newLine = "\n";
    const char* greenColour = "\x1b[32m";
    const char* resetColour = "\x1b[0m";

    va_list args;
    va_start( args, text );
    printf(greenColour);
    vprintf(text, args );
    va_end( args );
    printf(newLine);
    printf(resetColour);
}

void setConnectionType(char* connectionType) {
    _connectionType = connectionType;
    printDebugText("Connection type changed to %s", _connectionType);
}

char getConnectionType() {
    return _connectionType[0];
}

void setVoltage(char* value){
    printDebugText("Voltage changed from %s to %s", value, _voltage);
    _voltage = value;
}

float getVoltage() {
    return atof(_voltage);
}

int getNumberOfComponents(){
    return atof(_numberOfComponents);
}

void setNumberOfComponents(char* value){
    int oldNumberOfComponents = getNumberOfComponents();
    printDebugText("Number of components before change: %d, after: %s", oldNumberOfComponents, value);
    int i = 0;
    printDebugText("All values before changing the number of components:");
    while(i < oldNumberOfComponents){
        printDebugText("Position: %d had %s \n", i, _resistance[i]);
        i = i + 1;
    }
    _numberOfComponents = value;
    initResistanceListSection(_numberOfComponents, oldNumberOfComponents);
}
void setResistanceItemValue(int index, char* value) {
    _resistance[index-1] = value;
}

float* getResistanceItems(){
    float* resistance = malloc(getNumberOfComponents()*sizeof(float));
    int i = 0;
    while(i < getNumberOfComponents()){
        resistance[i] = atof(_resistance[i]);
        printDebugText("Value converted from: %s to: %f", _resistance[i], resistance[i]);
        i = i + 1;
    }
    return resistance;
}

void initResistanceListSection(int currentNumberOfComponents, int oldNumberOfComponents) {

    int i = 0;
    while(i < oldNumberOfComponents){
        free(_resistance[i]);
        i = i + 1;
    }

    free(_resistance);
    _resistance = malloc(sizeof(char*)*getNumberOfComponents());

    addInputSections(getNumberOfComponents(), oldNumberOfComponents, _resistance);
}

void voltageChanged (GtkEditable *editable,
               gpointer     user_data) {
    setVoltage(gtk_editable_get_chars(editable, 0,-1));
}

void connectionTypeChanged (GtkCheckButton* checkButton,
               gpointer     user_data) {
    gboolean isChecked = gtk_toggle_button_get_active (checkButton);
    if(isChecked == TRUE){
        setConnectionType("P");
    } else {
        setConnectionType("S");
    }
}

void numberOfComponentsChanged (GtkComboBox* comboBox,
               gpointer     user_data) {
    setNumberOfComponents(gtk_combo_box_text_get_active_text (comboBox));
}

static resistanceListItemChanged (GtkEditable *editable,
               gpointer     user_data) {
    if(user_data != NULL){
        char* value = gtk_editable_get_chars(editable, 0,-1);
        printDebugText("Resistance value with index %d was set to: %s\n", user_data, value);
        setResistanceItemValue(user_data, value);
    }
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

static void addOutputLabel(GtkGrid *grid, char* text, int col, int row) {
    GtkWidget* label = gtk_grid_get_child_at(_mainGrid, col, row);
    if(label == NULL){
        label = gtk_label_new(NULL);
        gtk_grid_attach(_mainGrid,label,col,row,1,1);
        gtk_widget_show(label);
    }
    gtk_label_set_text (label,text);
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
    addOutputLabel(_mainGrid, formatedMessage, 1, RESISTANCEOUTPUTLABELROW);
    sprintf(formatedMessage, "Effekt %.2f W", totalpower);
    addOutputLabel(_mainGrid, formatedMessage, 1, VOLTAGEOUTPUTLABELROW);
    sprintf(formatedMessage, "Ersättningsresistans i E12-serien koppliade i serie: %.0f, %.0f, %.0f", *replaceResistanceValues, *(replaceResistanceValues+1), *(replaceResistanceValues+2));
    addOutputLabel(_mainGrid, formatedMessage, 1, E12OUTPUTLABELROW);
}

static void addHeader(char *text, GtkGrid *grid, int col, int row){
    GtkWidget *label;

    label = gtk_label_new(NULL);
    const char *format = "<b>\%s</b>";
    char *markup;

    markup = g_markup_printf_escaped (format, text);
    gtk_label_set_markup (GTK_LABEL (label), markup);
    g_free (markup);
    
    gtk_grid_attach(grid, label, col, row, 1, 1);

    gtk_widget_show(label);
}

static void addInputSection(char *text, GtkGrid *grid, void (*entryChangedFuncPtr) (GtkEditable *editable, gpointer),
                            int col, int row, int* index) {
    GtkGrid *childGrid;
    GtkWidget *label;
    GtkWidget *textBox;

    childGrid = gtk_grid_new();
    label = gtk_label_new_with_mnemonic(text);
    textBox = gtk_entry_new();
    if(entryChangedFuncPtr != NULL){
        g_signal_connect(textBox, "changed", G_CALLBACK(entryChangedFuncPtr), index);
    }
    
    gtk_grid_attach_next_to(childGrid, label, NULL, GTK_POS_RIGHT,1,1);
    gtk_grid_attach_next_to(childGrid, textBox, label, GTK_POS_RIGHT,1,1);
    gtk_grid_attach(grid, childGrid, col, row, 1, 1);
    gtk_widget_show(childGrid);
    gtk_widget_show(textBox);
    gtk_widget_show(label);
}

void addInputSections(int numberOfComponents, int oldNumberOfComponents, char** resistanceList){
    
    GtkGrid* resistanceListGrid = gtk_grid_get_child_at(_mainGrid, 2, 2);
    gtk_container_remove(_mainGrid, resistanceListGrid);
    resistanceListGrid = gtk_grid_new();
    gtk_grid_attach(_mainGrid, resistanceListGrid, 2, 2, 1, 1);
    
    int i = 1;
    while(i <= numberOfComponents) {
        resistanceList[i-1] = malloc(sizeof(char)*20);
        resistanceList[i-1] = "0";
        int* index = malloc(sizeof(int));
        index = i;
        addInputSection("Komponent:", resistanceListGrid, resistanceListItemChanged, 1, i, index);
        i = i + 1;
    }

    gtk_widget_show(resistanceListGrid);
}

static void addCheckbox(char *text, GtkGrid *grid, void (*entryChangedFuncPtr) (GtkCheckButton *editable, gpointer), int col, int row){
    GtkWidget* checkBox = gtk_check_button_new_with_label ("Räkna med Parallell koppling \n istället för Seriell");

    g_signal_connect(checkBox, "toggled", G_CALLBACK(entryChangedFuncPtr), NULL);

    gtk_grid_attach(grid, checkBox, col, row, 1, 1);
    gtk_widget_show(checkBox);
}

static void addDropDownList(int numberOfElements, GtkGrid *grid, void (*entryChangedFuncPtr) (GtkComboBox *editable, gpointer),
                            int col, int row){
    GtkWidget* comboBoxWithText = gtk_combo_box_text_new_with_entry ();
    int i = 1;
    while(i <= numberOfElements){
        char *numberAsChar = malloc(20);
        sprintf(numberAsChar, "%d", i);
        gtk_combo_box_text_append (comboBoxWithText, numberAsChar, numberAsChar);
        i = i + 1;
    }

    gtk_combo_box_set_active_id (comboBoxWithText,"1");

    g_signal_connect(comboBoxWithText, "changed", G_CALLBACK(entryChangedFuncPtr), NULL);

    gtk_grid_attach(grid, comboBoxWithText, col, row, 1, 1);
    gtk_widget_show(comboBoxWithText);
}

int main(int argc, char *argv[]){
    printf("GTK...\n");
    GtkWidget *window;
    GtkWidget *button;

    gtk_init(&argc, &argv);
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    g_signal_connect(window, "delete-event", G_CALLBACK(delete_event), NULL);
    g_signal_connect(window, "destroy", G_CALLBACK(destroy), NULL);
    
   _mainGrid = gtk_grid_new();
    button = gtk_button_new_with_label("Beräkna!");
    

    g_signal_connect(button, "clicked", G_CALLBACK(button_clicked), NULL);

    //g_signal_connect_swapped(button, "clicked", G_CALLBACK(gtk_widget_destroy), window);

    gtk_container_add(GTK_CONTAINER(window),_mainGrid);
    
    addHeader("Ange basdata: ",_mainGrid, 1, 1);
    addInputSection("Ange spänningskälla i V: ",_mainGrid, voltageChanged, 1, 2,0);
    addCheckbox("Räkna med Parallell koppling istället för Seriell",_mainGrid, connectionTypeChanged, 1, 3);
    addDropDownList(10,_mainGrid, numberOfComponentsChanged, 1,4);

    
    addHeader("Komponenter och spänning: ",_mainGrid, 2, 1);
    initResistanceListSection(getNumberOfComponents(),0);
    
    gtk_grid_attach(_mainGrid, button, 1, 5,2,1);
    gtk_widget_show(_mainGrid);
    gtk_widget_show(button);
    gtk_widget_show(window);

    gtk_main();
    return 0;
}