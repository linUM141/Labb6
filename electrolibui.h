#ifndef ELECTROLIBUI
#define ELECTROLIBUI
/**
* @brief Calculate the resistance for either parallell or serial connections.
*
* Calculates the resistance values for either a series of components that are connected in parallell or serial.
* @param count The number of components
* @param conn The type of connection, can be either P(Parallell) or S(Serial)
* @param *array The resistance values of the components
* @return The summarized resistance value. If any of the input arguments are incorrect, -1 will be returned.
**/
void printDebugText(const char* text, ...);
void addInputSection(char *text, GtkGrid *grid, void (*entryChangedFuncPtr) (GtkEditable *editable, gpointer), int col, int row, int* index);
void addInputSections(int numberOfComponents, int oldNumberOfComponents, GtkGrid* mainGrid, void (*entryChangedFuncPtr) (GtkEditable *editable, gpointer));
void initResistanceListSection(int currentNumberOfComponents, int oldNumberOfComponents, char*** resistanceList, GtkGrid* mainGrid, void (*entryChangedFuncPtr) (GtkEditable *editable, gpointer));
void addOutputLabel(GtkGrid *grid, char* text, int col, int row, GtkGrid *mainGrid);
void addHeader(char *text, GtkGrid *grid, int col, int row);
void addCheckbox(char *text, GtkGrid *grid, void (*entryChangedFuncPtr) (GtkCheckButton *editable, gpointer), int col, int row);
void addDropDownList(int numberOfElements, GtkGrid *grid, void (*entryChangedFuncPtr) (GtkComboBox *editable, gpointer),
                            int col, int row);
GtkGrid* createWindowAndMainGrid(int argc, char *argv[], void (*destroyFuncPtr) (GtkWidget *widget, gpointer), void (*deleteEventFuncPtr) (GtkWidget *widget, GdkEvent *event, gpointer data));

#endif