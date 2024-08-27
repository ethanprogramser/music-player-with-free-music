#include<gtk/gtk.h>
#include<SFML/Audio/Music.hpp>
#include<iostream>
#include<string>
#include<bits/stdc++.h>
#include<json/json.h>
#include<fstream>
#include<vector>
#include<SFML/System.hpp>

GtkWidget *window;
GtkWidget *entry;
GtkWidget *play_button;
GtkWidget *search_field;
GtkWidget *rrewind;
GtkWidget *skip;
GtkWidget *search;
GtkWidget *box;
GtkWidget *entry2;
GtkWidget *play_2;
GtkWidget *selected_song;
GtkWidget *lp_button;
GtkWidget *lp_entry;

bool is_playing = false;

std::string current_song;


static void play(GtkWidget *button, gpointer *data) {
	sf::Music music;
	if(is_playing == false) { 
		if(!music.openFromFile(current_song)) {
			printf("error loading song...");
		}
		music.setVolume(50);
		music.play();
		gtk_button_set_label(GTK_BUTTON(play_button), "||");
		is_playing = true;
	}
	else {
		gtk_button_set_label(GTK_BUTTON(play_button), "|>");
		music.pause();
		is_playing = false;
	}
}

static void make_playlist(GtkWidget *b, gpointer *data) {
    
}

static void start_song(GtkWidget *button, gpointer *data) {
	sf::Music music;
	current_song = gtk_entry_get_text(GTK_ENTRY(entry2));
	std::cout << "now playing  " << current_song << "\n";
	music.openFromFile(current_song);
	gtk_label_set_text(GTK_LABEL(selected_song), current_song.c_str());
	music.play();
	gtk_button_set_label(GTK_BUTTON(play_button), "||");
	is_playing = true;
}

static void send_to(GtkWidget *button, gpointer *data) {
	std::string command = "source proj/bin/activate && python3 py.py";
	command = command + " " + gtk_entry_get_text(GTK_ENTRY(entry));
	system(command.c_str());
}

static void create_playlists(GtkWidget *button, gpointer *data) {
	std::ifstream playlist_value("playlists/p1.json", std::ifstream::binary);
	Json::Value playlist_options;
}

int main(int argc, char *argv[]) {

	gtk_init(&argc, &argv);

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	
	play_button = gtk_button_new_with_label("|>");
	rrewind = gtk_button_new_with_label("<-");
	skip = gtk_button_new_with_label("->");
	search = gtk_button_new_with_label("save");
	play_2 = gtk_button_new_with_label("play");
	selected_song = gtk_label_new_with_mnemonic("_No Song Selected");
	entry2 = gtk_entry_new();
	box = gtk_grid_new();
	entry = gtk_entry_new();
	lp_entry = gtk_entry_new();
	lp_button = gtk_button_new_with_label("load playlist");

	gtk_widget_set_halign(box, GTK_ALIGN_CENTER);
	gtk_widget_set_valign(box, GTK_ALIGN_END);
	gtk_grid_set_row_homogeneous(GTK_GRID(box), true);
	gtk_grid_set_column_homogeneous(GTK_GRID(box), true);


	gtk_container_add(GTK_CONTAINER(window), box);

	gtk_grid_attach(GTK_GRID(box), rrewind, 0, 0, 10, 10);
	gtk_grid_attach_next_to(GTK_GRID(box), selected_song, rrewind, GTK_POS_TOP, 30, 10);
	gtk_grid_attach_next_to(GTK_GRID(box), play_button, rrewind, GTK_POS_RIGHT, 10, 10);
	gtk_grid_attach_next_to(GTK_GRID(box), skip, play_button, GTK_POS_RIGHT, 10, 10);	 
	gtk_grid_attach_next_to(GTK_GRID(box), play_2, selected_song, GTK_POS_TOP, 10, 5);
	gtk_grid_attach_next_to(GTK_GRID(box), entry2, play_2, GTK_POS_TOP, 10, 5);
	gtk_grid_attach_next_to(GTK_GRID(box), entry, entry2, GTK_POS_RIGHT, 10, 5);
	gtk_grid_attach_next_to(GTK_GRID(box), search, play_2, GTK_POS_RIGHT, 10, 5);
	gtk_grid_attach_next_to(GTK_GRID(box), lp_entry, entry, GTK_POS_RIGHT, 10, 5);
	gtk_grid_attach_next_to(GTK_GRID(box), lp_button, search, GTK_POS_RIGHT, 10, 5);
	// gtk_grid_attach(GTK_GRID(box), rrewind, 0, 28, 10, 10);

	g_signal_connect(play_button, "clicked", G_CALLBACK(play), NULL);
	g_signal_connect(play_2, "clicked", G_CALLBACK(start_song), NULL);
	g_signal_connect(search, "clicked", G_CALLBACK(send_to), NULL);

 	gtk_widget_show_all(window);

	gtk_main();
	
	return 0;
}
