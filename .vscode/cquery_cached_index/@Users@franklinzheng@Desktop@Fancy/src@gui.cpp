#include "gui.hpp"
#include "main.h"
#include <stdlib.h>
#include <stdio.h>


static lv_obj_t * scr; // home screen
static lv_obj_t * autonSelectionScreen;
static lv_obj_t * actionScreen;
static lv_obj_t * autonLabel;
static lv_obj_t * mirrorLabel;

// --Screen 2 set up--
// can have up to 6 different autons (max is dependent on how many
// alignments are in alignArray)
const int autoCount = 6;
const char *autoNames[autoCount] = {
  "big boi",
  "platform",
  "flagAndPlat",
  "scrap boi 2",
  "scrap boi",
  "back auton"
};

//saves the auton number to the sd card
void setAuton(int autonNumber){

  FILE *fp;
  fp = fopen("/usd/auton.txt", "w");
  fprintf(fp, "%d", autonNumber);

  fclose(fp);
}

void setMirror(bool mirrorBool){

  FILE *fp;
  fp = fopen("/usd/mirror.txt", "w");
  if (mirrorBool){
    fprintf(fp, "%d", 1);
  } else {
    fprintf(fp, "%d", 0);
  }
  fclose(fp);
}

// ---------------------------------------
// ---------GUI HELPER METHODS------------
// ---------------------------------------

// draws a label
lv_obj_t *drawLabel( lv_align_t align, lv_style_t *style, lv_obj_t * scr, int x_offset) {

  /*lv_style_t *style1 = (lv_style_t *)malloc( sizeof( lv_style_t ));
  lv_style_copy(style1, &lv_style_plain_color);    //Copy a built-in style to initialize the new style
  style1->body.empty = 1;
  style1->body.border.color = color;
  style1->body.border.width = 1;
  style1->body.border.part = LV_BORDER_FULL;*/

  lv_obj_t *label = lv_label_create(scr, NULL);
  if (style != NULL)
    lv_obj_set_style(label, style);
  lv_obj_align(label, scr, align, x_offset, 0);
  return label;
}
// draws a button
lv_obj_t *drawButton(lv_style_t *style, lv_align_t align, lv_action_t action, int buttonNumber, lv_obj_t * scr, int x_offset) {
  // set styles


  //create button
  lv_obj_t *btn1 = lv_btn_create(scr, NULL);
  if (style != NULL)
    lv_obj_set_style(btn1, style);
  lv_cont_set_fit(btn1, true, true);
  lv_obj_align(btn1, scr, align, x_offset, 0);


  // set button number and action
  lv_obj_set_free_num(btn1, buttonNumber);   /*Set a unique number for the button*/
  lv_btn_set_action(btn1, LV_BTN_ACTION_CLICK, action);

  return btn1;
}

// action for testing when a button is click
static lv_res_t btn_click_action(lv_obj_t * btn)
{
  static lv_obj_t *label = lv_label_create(lv_scr_act(), NULL);
  uint8_t id = lv_obj_get_free_num(btn);
  char mytext[64];

  sprintf(mytext, "Button %d is released\n", id);
  lv_label_set_text(label, mytext);
  lv_obj_align(label, NULL, LV_ALIGN_IN_BOTTOM_MID, 0, 5);

  /* The button is released.
  * Make something here */

  return LV_RES_OK; /*Return OK if the button is not deleted*/
}

// action for when a screens selection button is cliked
static lv_res_t screen_btn_click_action(lv_obj_t * btn)
{
  uint8_t id = lv_obj_get_free_num(btn);
  if (id == 1) {
    lv_scr_load(scr);
  } else if (id == 2) {
    lv_scr_load(autonSelectionScreen);
  } else if (id == 3) {
    lv_scr_load(actionScreen);
  }
  /* The button is released.
  * Make something here */

  return LV_RES_OK; /*Return OK if the button is not deleted*/
}

// action for when an auton selection button is clicked
static lv_res_t auton_btn_click_action(lv_obj_t * btn)
{
  uint8_t id = lv_obj_get_free_num(btn);
  setAuton((int)id);

  char mytext[64];

  sprintf(mytext, "Auton %s is selected\n", autoNames[id]);
  lv_label_set_text(autonLabel, mytext);
  lv_obj_align(autonLabel, NULL, LV_ALIGN_IN_TOP_RIGHT, 0, -5);
  auton = id;
  /* The button is released.
  * Make something here */

  return LV_RES_OK; /*Return OK if the button is not deleted*/
}

// action for when an action selection button is clicked
static lv_res_t action_btn_click_action(lv_obj_t * btn)
{
  uint8_t id = lv_obj_get_free_num(btn);
  //no action rn
  /*if (id == 1)
      intakeBall();
  else if (id == 2)
      intakeBall();
  else if (id == 3)
      intakeBall();*/

  /* The button is released.
  * Make something here */

  return LV_RES_OK; /*Return OK if the button is not deleted*/
}

static lv_res_t mirror_btn_click_action(lv_obj_t * btn)
{
  if (mirror) {
    mirror = false;
    lv_label_set_text(mirrorLabel, "Mirror: false");
  } else {
    mirror = true;
    lv_label_set_text(mirrorLabel, "Mirror: true");
  }
  setMirror(mirror);
  /* The button is released.
  * Make something here */

  return LV_RES_OK; /*Return OK if the button is not deleted*/
}


// ---------------------------------------
// ----------MAIN GUI SET UP--------------
// ---------------------------------------
void gui(void) {
// create different styles
  lv_style_t *style1 = NULL; // or not :)
  lv_style_t *style2 = (lv_style_t *)malloc( sizeof( lv_style_t ));
  lv_style_copy(style2, &lv_style_plain_color);    //Copy a built-in style to initialize the new style
  style2->body.empty = 1;
  style2->body.border.color = LV_COLOR_BLUE;
  style2->body.border.width = 1;
  style2->body.border.part = LV_BORDER_FULL;
  style2->text.color = LV_COLOR_RED;

// Set up alignment array for aligning things created by loops
  const lv_align_t alignArray[6] = {
    LV_ALIGN_IN_LEFT_MID,
    LV_ALIGN_CENTER,
    LV_ALIGN_IN_RIGHT_MID,
    LV_ALIGN_IN_BOTTOM_LEFT,
    LV_ALIGN_IN_BOTTOM_MID,
    LV_ALIGN_IN_BOTTOM_RIGHT
  };

// SCREEN 1
  scr = lv_obj_create(NULL, NULL);
  lv_scr_load(scr);



 /*Create a title label*/
 lv_obj_t *label = drawLabel(LV_ALIGN_IN_TOP_MID, style2, scr, -50);
 lv_label_set_text(label, "Choose something to do");

 /*Create a normal button*/
 static lv_obj_t *btn1 = drawButton(style1, LV_ALIGN_IN_LEFT_MID, screen_btn_click_action, 2, scr, 15);
 label = lv_label_create(btn1, NULL);
 lv_label_set_text(label, "Auton Selection");

 static lv_obj_t *btn2 = drawButton(style1, LV_ALIGN_CENTER, screen_btn_click_action, 3, scr, 0);
 label = lv_label_create(btn2, NULL);
 lv_label_set_text(label, "Actions");

 static lv_obj_t *btn3 = drawButton(style1, LV_ALIGN_IN_RIGHT_MID, mirror_btn_click_action, 0, scr, 0);
 mirrorLabel = lv_label_create(btn3, NULL);
 lv_label_set_text(mirrorLabel, "Mirror: false");

// SCREEN 2 --- AUTON SELECTION SCREEN ---






  // --Screen 2 drawing--
  autonSelectionScreen = lv_obj_create(NULL, NULL);

  label = drawLabel(LV_ALIGN_IN_TOP_MID, style2, autonSelectionScreen, -50);
  lv_label_set_text(label, "Select an Auton");

  for (int i = 0; i < autoCount; i++) {
    btn1 = drawButton(style1, alignArray[i], auton_btn_click_action, i, autonSelectionScreen, 0);
    label = lv_label_create(btn1, NULL);
    lv_label_set_text(label, autoNames[i]);
  }

  autonLabel = drawLabel(LV_ALIGN_IN_TOP_RIGHT, style1, autonSelectionScreen, -130);
  char mytext[45];
  sprintf(mytext, "Auton %s is selected\n", autoNames[auton]);
  lv_label_set_text(autonLabel, mytext);

  btn1 = drawButton(style1, LV_ALIGN_IN_TOP_LEFT, screen_btn_click_action, 1, autonSelectionScreen, 0);
  label = lv_label_create(btn1, NULL);
  lv_label_set_text(label, "Back");
// ------------
// SCREEN 3
// ------------

  const int actionCount = 5;
  const char *actionNames[actionCount] = {
    "intake",
    "load catapult",
    "fire catapult",
    "cap lift up",
    "cap lift down"
  };

  actionScreen = lv_obj_create(NULL, NULL);


  label = drawLabel(LV_ALIGN_IN_TOP_MID, style2, actionScreen, -30);
  lv_label_set_text(label, "Select an Action");

  for (int i = 0; i < actionCount; i++) {
    btn1 = drawButton(style1, alignArray[i], action_btn_click_action, i, actionScreen, 0);
    label = lv_label_create(btn1, NULL);
    lv_label_set_text(label, actionNames[i]);
  }


  btn1 = drawButton(style1, LV_ALIGN_IN_TOP_LEFT, screen_btn_click_action, 1, actionScreen, 0);
  label = lv_label_create(btn1, NULL);
  lv_label_set_text(label, "Back");




}
