#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include <ctype.h>

typedef struct Client {
    int id;
    char name[50];
    char destination[50];
    float budget;
    struct Client* next;
} Client;

Client* addClient(Client* head, int id, char* name, char* destination, float budget);
void displayClients(Client* head, GtkWidget *output_label);
Client* searchClient(Client* head, int id);
Client* deleteClient(Client* head, int id);
int isValidInteger(const gchar *text);
int isValidFloat(const gchar *text);
int isValidString(const gchar *text);
void freeList(Client* head);

Client* head = NULL;

int isValidInteger(const gchar *text) {
    if (*text == '\0') return 0;
    while (*text) {
        if (!isdigit(*text)) return 0;
        text++;
    }
    return 1;
}

int isValidFloat(const gchar *text) {
    if (*text == '\0') return 0;
    int dot_count = 0;
    while (*text) {
        if (*text == '.') dot_count++;
        else if (!isdigit(*text)) return 0;
        text++;
    }
    return dot_count <= 1;
}

int isValidString(const gchar *text) {
    return text && strlen(text) > 0;
}

static void on_AddClientButton_clicked(GtkWidget *button, gpointer user_data) {
    GtkWidget **widgets = (GtkWidget **)user_data;
    GtkWidget *entry1 = widgets[0];
    GtkWidget *entry2 = widgets[1];
    GtkWidget *entry3 = widgets[2];
    GtkWidget *entry4 = widgets[3];
    GtkWidget *output_label = widgets[4];

    GtkEntryBuffer *buffer1 = gtk_entry_get_buffer(GTK_ENTRY(entry1));
    GtkEntryBuffer *buffer2 = gtk_entry_get_buffer(GTK_ENTRY(entry2));
    GtkEntryBuffer *buffer3 = gtk_entry_get_buffer(GTK_ENTRY(entry3));
    GtkEntryBuffer *buffer4 = gtk_entry_get_buffer(GTK_ENTRY(entry4));

    const gchar *text1 = gtk_entry_buffer_get_text(buffer1);
    const gchar *text2 = gtk_entry_buffer_get_text(buffer2);
    const gchar *text3 = gtk_entry_buffer_get_text(buffer3);
    const gchar *text4 = gtk_entry_buffer_get_text(buffer4);

    if (!isValidInteger(text1) || !isValidString(text2) || !isValidString(text3) || !isValidFloat(text4)) {
        gtk_label_set_text(GTK_LABEL(output_label), "Invalid input, please check fields.");
        return;
    }

    head = addClient(head, atoi(text1), (char*)text2, (char*)text3, atof(text4));
    if (head) {
        gtk_label_set_text(GTK_LABEL(output_label), "Client added successfully.");
    } else {
        gtk_label_set_text(GTK_LABEL(output_label), "Client ID already exists.");
    }
}

static void on_DeleteClientButton_clicked(GtkWidget *button, gpointer user_data) {
    GtkWidget **widgets = (GtkWidget **)user_data;
    GtkWidget *entry5 = widgets[5];
    GtkWidget *output_label = widgets[4];

    GtkEntryBuffer *buffer5 = gtk_entry_get_buffer(GTK_ENTRY(entry5));
    const gchar *text5 = gtk_entry_buffer_get_text(buffer5);

    if (!isValidInteger(text5)) {
        gtk_label_set_text(GTK_LABEL(output_label), "Invalid client ID for deletion.");
        return;
    }

    head = deleteClient(head, atoi(text5));
    gtk_label_set_text(GTK_LABEL(output_label), "Client deleted (if exists).");
}

static void on_SearchClientButton_clicked(GtkWidget *button, gpointer user_data) {
    GtkWidget **widgets = (GtkWidget **)user_data;
    GtkWidget *entry6 = widgets[6];
    GtkWidget *output_label = widgets[4];

    GtkEntryBuffer *buffer6 = gtk_entry_get_buffer(GTK_ENTRY(entry6));
    const gchar *text6 = gtk_entry_buffer_get_text(buffer6);

    if (!isValidInteger(text6)) {
        gtk_label_set_text(GTK_LABEL(output_label), "Invalid client ID for search.");
        return;
    }

    Client *client = searchClient(head, atoi(text6));
    if (client) {
        char output[200];
        sprintf(output, "Client found: ID: %d, Name: %s, Destination: %s, Budget: %.2f",
                client->id, client->name, client->destination, client->budget);
        gtk_label_set_text(GTK_LABEL(output_label), output);
    } else {
        gtk_label_set_text(GTK_LABEL(output_label), "Client not found.");
    }
}

static void on_DisplayClientsButton_clicked(GtkWidget *button, gpointer user_data) {
    GtkWidget **widgets = (GtkWidget **)user_data;
    GtkWidget *output_label = widgets[4];

    displayClients(head, output_label);
}

static void activate(GtkApplication *app, gpointer user_data) {
    GtkWidget *window;
    GtkWidget *main_box;
    GtkWidget *top_box;
    GtkWidget *mid_box;
    GtkWidget *entry1, *entry2, *entry3, *entry4, *entry5, *entry6;
    GtkWidget *AddClientButton, *DeleteClientButton, *SearchClientButton, *DisplayClientsButton;
    GtkWidget *output_label;

    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Agence de Voyage");
    gtk_window_set_default_size(GTK_WINDOW(window), 1800, 800);

    main_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 15);
    gtk_window_set_child(GTK_WINDOW(window), main_box);

    top_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_box_append(GTK_BOX(main_box), top_box);

    mid_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_box_append(GTK_BOX(main_box), mid_box);

    GtkWidget *label1 = gtk_label_new("Client ID (unique):");
    entry1 = gtk_entry_new();
    gtk_box_append(GTK_BOX(top_box), label1);
    gtk_box_append(GTK_BOX(top_box), entry1);

    GtkWidget *label2 = gtk_label_new("Client Name:");
    entry2 = gtk_entry_new();
    gtk_box_append(GTK_BOX(top_box), label2);
    gtk_box_append(GTK_BOX(top_box), entry2);

    GtkWidget *label3 = gtk_label_new("Destination:");
    entry3 = gtk_entry_new();
    gtk_box_append(GTK_BOX(top_box), label3);
    gtk_box_append(GTK_BOX(top_box), entry3);

    GtkWidget *label4 = gtk_label_new("Budget:");
    entry4 = gtk_entry_new();
    gtk_box_append(GTK_BOX(top_box), label4);
    gtk_box_append(GTK_BOX(top_box), entry4);

    AddClientButton = gtk_button_new_with_label("Add a client");
    gtk_box_append(GTK_BOX(top_box), AddClientButton);

    GtkWidget *label5 = gtk_label_new("Client ID to delete:");
    entry5 = gtk_entry_new();
    gtk_box_append(GTK_BOX(top_box), label5);
    gtk_box_append(GTK_BOX(top_box), entry5);

    DeleteClientButton = gtk_button_new_with_label("Delete a client");
    gtk_box_append(GTK_BOX(top_box), DeleteClientButton);

    GtkWidget *label6 = gtk_label_new("Client ID to search:");
    entry6 = gtk_entry_new();
    gtk_box_append(GTK_BOX(top_box), label6);
    gtk_box_append(GTK_BOX(top_box), entry6);

    SearchClientButton = gtk_button_new_with_label("Search a client");
    gtk_box_append(GTK_BOX(top_box), SearchClientButton);

    DisplayClientsButton = gtk_button_new_with_label("Display clients");
    gtk_box_append(GTK_BOX(top_box), DisplayClientsButton);

    output_label = gtk_label_new("Enter text above and press Submit.");
    gtk_widget_set_halign(output_label, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(output_label, GTK_ALIGN_CENTER);
    gtk_box_append(GTK_BOX(main_box), output_label);

    GtkWidget **widgets = g_new(GtkWidget *, 7);
    widgets[0] = entry1;
    widgets[1] = entry2;
    widgets[2] = entry3;
    widgets[3] = entry4;
    widgets[4] = output_label;
    widgets[5] = entry5;
    widgets[6] = entry6;

    g_signal_connect(AddClientButton, "clicked", G_CALLBACK(on_AddClientButton_clicked), widgets);
    g_signal_connect(DeleteClientButton, "clicked", G_CALLBACK(on_DeleteClientButton_clicked), widgets);
    g_signal_connect(SearchClientButton, "clicked", G_CALLBACK(on_SearchClientButton_clicked), widgets);
    g_signal_connect(DisplayClientsButton, "clicked", G_CALLBACK(on_DisplayClientsButton_clicked), widgets);

    gtk_window_present(GTK_WINDOW(window));
}

int main(int argc, char* argv[]) {
    GtkApplication *app;
    int status;

    app = gtk_application_new("org.gtk.example.enhancedinput", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    freeList(head);
    return status;
}

Client* addClient(Client* head, int id, char* name, char* destination, float budget) {
    Client* temp = head;
    while (temp) {
        if (temp->id == id) {
            return NULL;
        }
        temp = temp->next;
    }

    Client* newClient = (Client*)malloc(sizeof(Client));
    newClient->id = id;
    strcpy(newClient->name, name);
    strcpy(newClient->destination, destination);
    newClient->budget = budget;
    newClient->next = head;
    printf("Client added successfully.\n");
    return newClient;
}

void displayClients(Client* head, GtkWidget *output_label) {
    if (!head) {
        gtk_label_set_text(GTK_LABEL(output_label), "No clients in the database.");
        return;
    }

    char output[500] = "\n--- Client List ---\n";
    Client* temp = head;
    while (temp) {
        char client_info[200];
        sprintf(client_info, "ID: %d, Name: %s, Destination: %s, Budget: %.2f\n",
                temp->id, temp->name, temp->destination, temp->budget);
        strcat(output, client_info);
        temp = temp->next;
    }
    gtk_label_set_text(GTK_LABEL(output_label), output);
}

Client* searchClient(Client* head, int id) {
    Client* temp = head;
    while (temp) {
        if (temp->id == id) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

Client* deleteClient(Client* head, int id) {
    Client* temp = head;
    Client* prev = NULL;

    while (temp && temp->id != id) {
        prev = temp;
        temp = temp->next;
    }

    if (!temp) {
        printf("Client with ID %d not found.\n", id);
        return head;
    }

    if (!prev) {
        head = temp->next;
    } else {
        prev->next = temp->next;
    }

    free(temp);
    printf("Client with ID %d deleted.\n", id);
    return head;
}

void freeList(Client* head) {
    Client* temp;
    while (head) {
        temp = head;
        head = head->next;
        free(temp);
    }
}
