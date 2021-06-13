// List that stores the note values
int notes[29];

// Frequencies of notes starting with G5, G4, and G3 respectively
int notesHigh[] = {392, 416, 440, 466, 494, 524, 554, 588, 622, 660, 698, 740};
int notesMed[] = {196, 208, 220, 233, 247, 262, 277, 294, 311, 330, 349, 370};
int notesLow[] = {98, 104, 110, 117, 124, 131, 139, 147, 156, 165, 175, 185};

// Initialize variables for storing button input values
int str_one_s, str_two_s, str_three_s, str_four_s;
int butt_one_s, butt_two_s, butt_three_s, butt_four_s, butt_five_s, butt_six_s, butt_seven_s;
int pot_oct_v, pot_fine_v;

// Assign Pins
int current_note;
int speaker = A0;

int str_one = 2;
int str_two = 3;
int str_three = 4;
int str_four = 5;

int butt_one = 6;
int butt_two = 7;
int butt_three = 8;
int butt_four = 9;
int butt_five = 10;
int butt_six = 13;
int butt_seven = 12;

int pot_oct = A2;
int pot_fine = A5;

// Setup
void setup() {
  // Determine Pin Mode
  pinMode(str_one, INPUT);
  pinMode(str_two, INPUT);
  pinMode(str_three, INPUT);
  pinMode(str_four, INPUT);

  pinMode(butt_one, INPUT);
  pinMode(butt_two, INPUT);
  pinMode(butt_three, INPUT);
  pinMode(butt_four, INPUT);
  pinMode(butt_five, INPUT);
  pinMode(butt_six, INPUT);
  pinMode(butt_seven, INPUT);

  pinMode(pot_oct, INPUT);
  pinMode(pot_fine, INPUT);

  pinMode(speaker, OUTPUT);
}

// Main Loop
void loop() {

  // Functions for updating Sensory Values and notes pitch
  read_par();
  update_notes(pot_oct_v, pot_fine_v);

  // 4 whiles that loops continuously as one of the 4 str buttons is pressed
  while (str_one_s == 1) {

    // Updates values
    read_par();
    current_note = highest_position();

    // Playes tone from speaker
    tone(speaker, notes[current_note]);
  }

  // Loops repeat 4x for each string
  while (str_two_s == 1) {
    read_par();
    current_note = highest_position() + 7;
    tone(speaker, notes[current_note]);
  }
  while (str_three_s == 1) {
    read_par();
    current_note = highest_position() + 14;
    tone(speaker, notes[current_note]);
  }
  while (str_four_s == 1) {
    read_par();
    current_note = highest_position() + 21;
    tone(speaker, notes[current_note]);
  }

  // No note is played when none of the 4 strings are pressed
  while (str_one_s == 0 and str_two_s == 0 and str_three_s == 0 and str_four_s == 0) {
    read_par();
    noTone(speaker);
  }
}

// Function that re-reads the button and pot values
void read_par() {
  str_one_s = digitalRead(str_one);
  str_two_s = digitalRead(str_two);
  str_three_s = digitalRead(str_three);
  str_four_s = digitalRead(str_four);

  butt_one_s = digitalRead(butt_one);
  butt_two_s = digitalRead(butt_two);
  butt_three_s = digitalRead(butt_three);
  butt_four_s = digitalRead(butt_four);
  butt_five_s = digitalRead(butt_five);
  butt_six_s = digitalRead(butt_six);
  butt_seven_s = digitalRead(butt_seven);

  pot_oct_v = analogRead(pot_oct);
  pot_fine_v = analogRead(pot_fine);
}

// Determines the highest position pressed by left hand (0 = open string, 7 = highest button)
int highest_position() {
  
  if (butt_seven_s == 1) {
    return (7);
  }
  else if (butt_six_s == 1) {
    return (6);
  }
  else if (butt_five_s == 1) {
    return (5);
  }
  else if (butt_four_s == 1) {
    return (4);
  }
  else if (butt_three_s == 1) {
    return (3);
  }
  else if (butt_two_s == 1) {
    return (2);
  }
  else if (butt_one_s == 1) {
    return (1);
  }
  else {
    return (0);
  }
}

// Function that inputs the octave and fine tuning pegs values to update list of pitches
void update_notes(int pot_oct_v, int pot_fine_v) {
  float add_tone;
  add_tone = map(pot_fine_v, 0, 1023, 0, 1000);

  // Reads value of octave peg and makes the pitches +oct, -oct and oct 
  if (pot_oct_v < 341) {
    for (int i = 0; i < 12; i ++) {

      // the * (1 + (add_tone / 1000)) outputs a value from 1 to 2, taking advantage of the 
      // fact that F(Hz) * 1 does not change the pitch and F(Hz) * 2 jumps an octave
      notes[i] = notesHigh[i] * (1 + (add_tone / 1000));
    }
  }
  else if (pot_oct_v > 682) {
    for (int i = 0; i < 12; i ++) {
      notes[i] = notesLow[i] * (1 + (add_tone / 1000));
    }
  }
  else {
    for (int i = 0; i < 12; i ++) {
      notes[i] = notesMed[i] * (1 + (add_tone / 1000));
    }
  }

  // filling out the entire range of the instruments of 29 notes using the 12 given pitches
  for (int i = 0; i < 12; i ++) {
    notes[i] = notes[i];
  }
  
  for (int i = 12; i < 24; i ++) {
    notes[i] = notes[i - 12] * 2;
  }
  for (int i = 24; i < 29; i ++) {
    notes[i] = notes[i - 24] * 4;
  }
}
