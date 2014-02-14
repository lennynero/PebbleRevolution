// Copyright (c) 2013 Douwe Maan <http://www.douwemaan.com/>
// The above copyright notice shall be included in all copies or substantial portions of the program.

// Envisioned as a watchface by Jean-Noël Mattern
// Based on the display of the Freebox Revolution, which was designed by Philippe Starck.

#include <pebble.h>
#include <pebble_fonts.h>

// Settings
#define USE_AMERICAN_DATE_FORMAT      false
#define VIBE_ON_HOUR                  false
#define TIME_SLOT_ANIMATION_DURATION  500
#define USE_IT_DAYS_LANG              true
#define DEBUGLOG					  0

// Magic numbers
#define SCREEN_WIDTH        144
#define SCREEN_HEIGHT       168

#define BT_IMAGE_WIDTH     8
#define BT_IMAGE_HEIGHT    13
	
#define LOGO_IMAGE_WIDTH     70
#define LOGO_IMAGE_HEIGHT    7
	
#define BATTERY_IMAGE_WIDTH     30
#define BATTERY_IMAGE_HEIGHT    13

#define TIME_IMAGE_WIDTH_HH    60
#define TIME_IMAGE_HEIGHT_HH   60

#define TIME_IMAGE_WIDTH    70
#define TIME_IMAGE_HEIGHT   70

#define DATE_IMAGE_WIDTH    20
#define DATE_IMAGE_HEIGHT   20

#define MONTH_IMAGE_WIDTH     31
#define MONTH_IMAGE_HEIGHT    13
	
/*#define SECOND_IMAGE_WIDTH  10
#define SECOND_IMAGE_HEIGHT 10*/

#define YEARS_20_IMAGE_WIDTH  17
#define YEARS_20_IMAGE_HEIGHT 8

#define YEAR_IMAGE_WIDTH  8
#define YEAR_IMAGE_HEIGHT 8
	
#define DAY_IMAGE_WIDTH     25
#define DAY_IMAGE_HEIGHT    15

#define MARGIN              1
#define TIME_SLOT_SPACE     2
#define DATE_PART_SPACE     4
#define TOP_MARGIN			14

enum {
	PK_SETTINGS = 0,
	PK_INTL_FMT_DATE = 1,
	PK_INTL_AMPM_FORMAT = 2,
	PK_INTL_LANG = 3,
};

// Images
#define NUMBER_OF_TIME_IMAGES 20
const int TIME_IMAGE_RESOURCE_IDS[NUMBER_OF_TIME_IMAGES] = {
   RESOURCE_ID_IMAGE_TIME_0_HH, 
  RESOURCE_ID_IMAGE_TIME_1_HH, RESOURCE_ID_IMAGE_TIME_2_HH, 
RESOURCE_ID_IMAGE_TIME_3_HH, 
  RESOURCE_ID_IMAGE_TIME_4_HH, RESOURCE_ID_IMAGE_TIME_5_HH, 
RESOURCE_ID_IMAGE_TIME_6_HH, 
  RESOURCE_ID_IMAGE_TIME_7_HH, RESOURCE_ID_IMAGE_TIME_8_HH, 
RESOURCE_ID_IMAGE_TIME_9_HH, RESOURCE_ID_IMAGE_TIME_0, 
  RESOURCE_ID_IMAGE_TIME_1, RESOURCE_ID_IMAGE_TIME_2, RESOURCE_ID_IMAGE_TIME_3, 
  RESOURCE_ID_IMAGE_TIME_4, RESOURCE_ID_IMAGE_TIME_5, RESOURCE_ID_IMAGE_TIME_6, 
  RESOURCE_ID_IMAGE_TIME_7, RESOURCE_ID_IMAGE_TIME_8, RESOURCE_ID_IMAGE_TIME_9
};

#define NUMBER_OF_DAY_IMAGES 7
const int DAY_IMAGE_RESOURCE_IDS_EN[NUMBER_OF_DAY_IMAGES] = {
  RESOURCE_ID_IMAGE_DAY_0_EN, RESOURCE_ID_IMAGE_DAY_1_EN, RESOURCE_ID_IMAGE_DAY_2_EN, 
  RESOURCE_ID_IMAGE_DAY_3_EN, RESOURCE_ID_IMAGE_DAY_4_EN, RESOURCE_ID_IMAGE_DAY_5_EN, 
  RESOURCE_ID_IMAGE_DAY_6_EN
};

// Italian Days
const int DAY_IMAGE_RESOURCE_IDS_IT[NUMBER_OF_DAY_IMAGES] = {
  RESOURCE_ID_IMAGE_DAY_0_IT, RESOURCE_ID_IMAGE_DAY_1_IT, 
RESOURCE_ID_IMAGE_DAY_2_IT, 
  RESOURCE_ID_IMAGE_DAY_3_IT, RESOURCE_ID_IMAGE_DAY_4_IT, 
RESOURCE_ID_IMAGE_DAY_5_IT, 
  RESOURCE_ID_IMAGE_DAY_6_IT
};

#define NUMBER_OF_DATE_IMAGES 10
const int DATE_IMAGE_RESOURCE_IDS[NUMBER_OF_DATE_IMAGES] = {
  RESOURCE_ID_IMAGE_DATE_0, 
  RESOURCE_ID_IMAGE_DATE_1, RESOURCE_ID_IMAGE_DATE_2, RESOURCE_ID_IMAGE_DATE_3, 
  RESOURCE_ID_IMAGE_DATE_4, RESOURCE_ID_IMAGE_DATE_5, RESOURCE_ID_IMAGE_DATE_6, 
  RESOURCE_ID_IMAGE_DATE_7, RESOURCE_ID_IMAGE_DATE_8, RESOURCE_ID_IMAGE_DATE_9
};

#define NUMBER_OF_MONTH_IMAGES 12
const int MONTH_IMAGE_RESOURCE_IDS_IT[NUMBER_OF_MONTH_IMAGES] = {
  RESOURCE_ID_IMAGE_MONTH_0_IT, 
  RESOURCE_ID_IMAGE_MONTH_1_IT, RESOURCE_ID_IMAGE_MONTH_2_IT, 
RESOURCE_ID_IMAGE_MONTH_3_IT, 
  RESOURCE_ID_IMAGE_MONTH_4_IT, RESOURCE_ID_IMAGE_MONTH_5_IT, 
RESOURCE_ID_IMAGE_MONTH_6_IT, 
  RESOURCE_ID_IMAGE_MONTH_7_IT, RESOURCE_ID_IMAGE_MONTH_8_IT, 
RESOURCE_ID_IMAGE_MONTH_9_IT,
  RESOURCE_ID_IMAGE_MONTH_10_IT, RESOURCE_ID_IMAGE_MONTH_11_IT
};

const int MONTH_IMAGE_RESOURCE_IDS_EN[NUMBER_OF_MONTH_IMAGES] = {
  RESOURCE_ID_IMAGE_MONTH_0_EN, 
  RESOURCE_ID_IMAGE_MONTH_1_IT, RESOURCE_ID_IMAGE_MONTH_2_IT, 
RESOURCE_ID_IMAGE_MONTH_3_IT, 
  RESOURCE_ID_IMAGE_MONTH_4_EN, RESOURCE_ID_IMAGE_MONTH_5_EN, 
RESOURCE_ID_IMAGE_MONTH_6_EN, 
  RESOURCE_ID_IMAGE_MONTH_7_EN, RESOURCE_ID_IMAGE_MONTH_8_EN, 
RESOURCE_ID_IMAGE_MONTH_9_EN,
  RESOURCE_ID_IMAGE_MONTH_10_IT, RESOURCE_ID_IMAGE_MONTH_11_EN
};

/*#define NUMBER_OF_SECOND_IMAGES 10
const int SECOND_IMAGE_RESOURCE_IDS[NUMBER_OF_SECOND_IMAGES] = {
  RESOURCE_ID_IMAGE_SECOND_0, 
  RESOURCE_ID_IMAGE_SECOND_1, RESOURCE_ID_IMAGE_SECOND_2, RESOURCE_ID_IMAGE_SECOND_3, 
  RESOURCE_ID_IMAGE_SECOND_4, RESOURCE_ID_IMAGE_SECOND_5, RESOURCE_ID_IMAGE_SECOND_6, 
  RESOURCE_ID_IMAGE_SECOND_7, RESOURCE_ID_IMAGE_SECOND_8, RESOURCE_ID_IMAGE_SECOND_9
};*/

#define NUMBER_OF_YEAR_IMAGES 10
const int YEAR_IMAGE_RESOURCE_IDS[NUMBER_OF_YEAR_IMAGES] = {
  RESOURCE_ID_IMAGE_YEAR_0, 
  RESOURCE_ID_IMAGE_YEAR_1, RESOURCE_ID_IMAGE_YEAR_2, 
RESOURCE_ID_IMAGE_YEAR_3, 
  RESOURCE_ID_IMAGE_YEAR_4, RESOURCE_ID_IMAGE_YEAR_5, 
RESOURCE_ID_IMAGE_YEAR_6, 
  RESOURCE_ID_IMAGE_YEAR_7, RESOURCE_ID_IMAGE_YEAR_8, 
RESOURCE_ID_IMAGE_YEAR_9
};

// Global variables
struct tm *tick_time;
static Window *window;

// Header
static Layer *header_layer;

typedef struct ImageItem {
  GBitmap     *image;
  BitmapLayer *image_layer;
  Layer       *layer;
  bool        loaded;
} ImageItem;
static ImageItem bt_item, logo_item, day_item, month_item, years_20_item, meridiem_item;

// Footer
static Layer *footer_layer;
int footer_height = SCREEN_HEIGHT - SCREEN_WIDTH;

#define EMPTY_SLOT -1
typedef struct Slot {
  int         number;
  GBitmap     *image;
  BitmapLayer *image_layer;
  int         state;
} Slot;

// Battery
typedef struct BatteryItem {
  GBitmap     *image;
  BitmapLayer *image_layer;
  Layer       *layer;
  bool        loaded;
  TextLayer	  *text_layer;
} BatteryItem;
static BatteryItem battery_item;

// Time
typedef struct TimeSlot {
  Slot              slot;
  int               new_state;
  PropertyAnimation *slide_out_animation;
  PropertyAnimation *slide_in_animation;
  bool              updating;
  int 				slot_size;
} TimeSlot;

#define NUMBER_OF_TIME_SLOTS 4
static Layer *time_layer;
static TimeSlot time_slots[NUMBER_OF_TIME_SLOTS];

// Date
#define NUMBER_OF_DATE_SLOTS 2
static Layer *date_layer;
static Slot date_slots[NUMBER_OF_DATE_SLOTS];

// Seconds
/*#define NUMBER_OF_SECOND_SLOTS 2
static Layer *seconds_layer;
static Slot second_slots[NUMBER_OF_SECOND_SLOTS];*/

// Years
#define NUMBER_OF_YEAR_SLOTS 2
static Layer *years_layer;
static Slot year_slots[NUMBER_OF_YEAR_SLOTS];

// Create a struct to hold our persistent settings...
typedef struct persist {
  bool date_format;            // date format
  bool ampm_format;            // 24H format
  uint8_t lang;            // IT
} __attribute__((__packed__)) persist;

persist settings = {
  .date_format = false, // DD Month
  .ampm_format = false, // 24H
  .lang = 0 // IT
};

// General
void destroy_property_animation(PropertyAnimation **prop_animation);
BitmapLayer *load_digit_image_into_slot(Slot *slot, int digit_value, Layer *parent_layer, GRect frame, const int *digit_resource_ids);
void unload_digit_image_from_slot(Slot *slot);

void load_image_item(ImageItem* image_item, const int image_resource_id);
void unload_image_item(ImageItem* image_item);
void destroy_image_item(ImageItem* image_item);

void display_bluetooth(bool connected);

void display_battery();
void unload_battery_item();

// Time
void display_time(struct tm *tick_time);
void display_time_value(int value, int row_number);
void update_time_slot(TimeSlot *time_slot, int digit_value);
GRect frame_for_time_slot(TimeSlot *time_slot);
void slide_in_digit_image_into_time_slot(TimeSlot *time_slot, int digit_value);
void time_slot_slide_in_animation_stopped(Animation *slide_in_animation, bool finished, void *context);
void slide_out_digit_image_from_time_slot(TimeSlot *time_slot);
void time_slot_slide_out_animation_stopped(Animation *slide_out_animation, bool finished, void *context);

// Meridiem
int get_ampm_hour(struct tm *tick_time);
void set_ampm(int hour);

// Day
void display_day(struct tm *tick_time);
void unload_day_item();

// Date
void display_date(struct tm *tick_time);
void display_date_value(int value, int part_number);
void update_date_slot(Slot *date_slot, int digit_value);

// Month
void predisplay_month(int format);
void display_month(struct tm *tick_time);
void unload_month_item();

// Seconds
/*void display_seconds(struct tm *tick_time);
void update_second_slot(Slot *second_slot, int digit_value);*/

// Years
void display_years(struct tm *tick_time);
void update_year_slot(Slot *year_slot, int digit_value);

// Handlers
int main(void);
void init();

void in_configuration_handler(DictionaryIterator *received, void *context);

void handle_tick(struct tm *tick_time, TimeUnits units_changed);
void handle_bluetooth(bool connected);
void handle_battery();

void deinit();

void load_image_item(ImageItem *item, const int resource) {
  unload_image_item(item);

  item->image = gbitmap_create_with_resource(resource);  
  item->image_layer = bitmap_layer_create(item->image->bounds);
  bitmap_layer_set_bitmap(item->image_layer, item->image);
  layer_add_child(item->layer, bitmap_layer_get_layer(item->image_layer));

  item->loaded = true;
	if (DEBUGLOG) { APP_LOG(APP_LOG_LEVEL_DEBUG, "image loaded"); }
}

void unload_image_item(ImageItem *item) {
  if (!item->loaded) 
    return;

  layer_remove_from_parent(bitmap_layer_get_layer(item->image_layer));
  bitmap_layer_destroy(item->image_layer);
  gbitmap_destroy(item->image);

  item->loaded = false;
	if (DEBUGLOG) { APP_LOG(APP_LOG_LEVEL_DEBUG, "image unloaded"); }
}

void destroy_image_item(ImageItem *item){
  unload_image_item(item);
	
  layer_destroy(item->layer);
	if (DEBUGLOG) { APP_LOG(APP_LOG_LEVEL_DEBUG, "image destroyed"); }
}

// BT
void handle_bluetooth(bool connected) {	
  vibes_short_pulse();
	
  layer_set_hidden(bt_item.layer, !connected);
}

// Battery
void handle_battery(BatteryChargeState charge_state) {
  static char battery_text[] = "****";

  if (charge_state.is_charging) {
	snprintf(battery_text, sizeof(battery_text), "++++");
  } else {
	snprintf(battery_text, sizeof(battery_text), "%dH", 168*charge_state.charge_percent/100);
  }
  text_layer_set_text(battery_item.text_layer, battery_text);
}

void display_battery(Layer* root) {
  unload_battery_item();

  battery_item.image = 
gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BATTERY);
  
  battery_item.image_layer = 
bitmap_layer_create(battery_item.image->bounds);
  bitmap_layer_set_bitmap(battery_item.image_layer, battery_item.image);
  layer_add_child(battery_item.layer, 
bitmap_layer_get_layer(battery_item.image_layer));
  
  battery_item.loaded = true;
	
  TextLayer *battery_layer = text_layer_create(GRect(-4, -2, SCREEN_WIDTH, 
SCREEN_HEIGHT));
  text_layer_set_text_color(battery_layer, GColorWhite);
  text_layer_set_background_color(battery_layer, GColorClear);
  text_layer_set_font(battery_layer, 
fonts_get_system_font(FONT_KEY_GOTHIC_14));
  text_layer_set_text_alignment(battery_layer, GTextAlignmentCenter);
  text_layer_set_text_alignment(battery_layer, GAlignTopRight);
  	  
  battery_item.text_layer = battery_layer;
  layer_add_child(root, (Layer*)battery_item.text_layer);
	
  handle_battery(battery_state_service_peek());
}

void unload_battery_item() {
  if (!battery_item.loaded) 
    return;
  
  layer_remove_from_parent(text_layer_get_layer(battery_item.text_layer));
  text_layer_destroy(battery_item.text_layer);  
    
  layer_remove_from_parent(bitmap_layer_get_layer(battery_item.image_layer));
  bitmap_layer_destroy(battery_item.image_layer);

  gbitmap_destroy(battery_item.image);
}

// Animations
void destroy_property_animation(PropertyAnimation **animation) {
  if (*animation == NULL)
    return;

  if (animation_is_scheduled((Animation *)*animation)) {
    animation_unschedule((Animation *)*animation);
  }

  property_animation_destroy(*animation);
  *animation = NULL;
}

BitmapLayer *load_digit_image_into_slot(Slot *slot, int digit_value, Layer *parent_layer, GRect frame, const int *digit_resource_ids) {
  if (digit_value < 0 || digit_value > 19)
    return NULL;

  if (slot->state != EMPTY_SLOT)
    return NULL;

  slot->state = digit_value;

  slot->image = gbitmap_create_with_resource(digit_resource_ids[digit_value]);

  slot->image_layer = bitmap_layer_create(frame);
  bitmap_layer_set_bitmap(slot->image_layer, slot->image);
  layer_add_child(parent_layer, bitmap_layer_get_layer(slot->image_layer));

  return slot->image_layer;
}

void unload_digit_image_from_slot(Slot *slot) {
  if (slot->state == EMPTY_SLOT)
    return;

  layer_remove_from_parent(bitmap_layer_get_layer(slot->image_layer));
  bitmap_layer_destroy(slot->image_layer);

  gbitmap_destroy(slot->image);

  slot->state = EMPTY_SLOT;
}

// Time
void display_time(struct tm *tick_time) {
  int hour = get_ampm_hour(tick_time);
  
  set_ampm(hour);
  display_time_value(hour, 0);
  display_time_value(tick_time->tm_min, 1);
}

int get_ampm_hour(struct tm *tick_time){
  int hour = tick_time->tm_hour;
  
  if (!clock_is_24h_style() || settings.ampm_format) {
    hour = hour % 12;
    if (hour == 0) {
      hour = 12;
    }
  }
  return hour;
}

void set_ampm(int hour){
	if(settings.ampm_format){		
      if(tick_time->tm_hour < 12) {
		load_image_item(&meridiem_item, RESOURCE_ID_IMAGE_ANTE_MERIDIEM);
		if (DEBUGLOG) { APP_LOG(APP_LOG_LEVEL_DEBUG, "loaded AM"); }
	  }else {
	  	load_image_item(&meridiem_item, RESOURCE_ID_IMAGE_POST_MERIDIEM);
	  	if (DEBUGLOG) { APP_LOG(APP_LOG_LEVEL_DEBUG, "loaded PM"); }
	  }	
	}else{
	  unload_image_item(&meridiem_item);
	  if (DEBUGLOG) { APP_LOG(APP_LOG_LEVEL_DEBUG, "unloaded AM/PM"); }
	}
}

void display_time_value(int value, int row_number) {
  value = value % 100; // Maximum of two digits per row.

  for (int column_number = 1; column_number >= 0; column_number--) {
    int time_slot_number = (row_number * 2) + column_number;

    TimeSlot *time_slot = &time_slots[time_slot_number];

    update_time_slot(time_slot, value % 10 + (10 * row_number));

    value = value / 10;
  }
}

void update_time_slot(TimeSlot *time_slot, int digit_value) {
  if (time_slot->slot.state == digit_value)
    return;

  if (time_slot->updating) {
    // Otherwise we'll crash when the animation is replaced by a new animation before we're finished.
    return;
  }

  if (time_slot->slot.state == EMPTY_SLOT) {
    //slide_in_digit_image_into_time_slot(time_slot, digit_value);
	GRect frame = frame_for_time_slot(time_slot);
    load_digit_image_into_slot(&time_slot->slot, digit_value, time_layer, frame, TIME_IMAGE_RESOURCE_IDS);  
  }
  else {
	time_slot->updating = true;
    time_slot->new_state = digit_value;
    slide_out_digit_image_from_time_slot(time_slot);
  }
}

GRect frame_for_time_slot(TimeSlot *time_slot) {
  int time_image_size = time_slot->slot_size;
  
  int extra_left = 10;	
  int extra_top = TOP_MARGIN;
  if(time_slot->slot_size > TIME_IMAGE_WIDTH_HH) {
    extra_left = 0;
	extra_top = 3;
  }
	
  int x = extra_left + MARGIN + (time_slot->slot.number % 2) * (time_image_size + TIME_SLOT_SPACE);
  int y = extra_top + MARGIN + (time_slot->slot.number / 2) * (time_image_size + TIME_SLOT_SPACE);

  return GRect(x, y, time_image_size, time_image_size);
}

void slide_in_digit_image_into_time_slot(TimeSlot *time_slot, int digit_value) {
  int time_image_size = time_slot->slot_size;

  destroy_property_animation(&time_slot->slide_in_animation);

  GRect to_frame = frame_for_time_slot(time_slot);

  int from_x = to_frame.origin.x;
  int from_y = to_frame.origin.y;
  switch (time_slot->slot.number) {
    case 0:
      from_x -= time_image_size + MARGIN;
      break;
    case 1:
      from_y -= time_image_size + MARGIN;
      break;
    case 2:
      from_y += time_image_size + MARGIN;
      break;
    case 3:
      from_x += time_image_size + MARGIN;
      break;
  }
  GRect from_frame = GRect(from_x, from_y, time_image_size, time_image_size);

  BitmapLayer *image_layer = load_digit_image_into_slot(&time_slot->slot, digit_value, time_layer, from_frame, TIME_IMAGE_RESOURCE_IDS);

  time_slot->slide_in_animation = property_animation_create_layer_frame(bitmap_layer_get_layer(image_layer), &from_frame, &to_frame);

  Animation *animation = (Animation *)time_slot->slide_in_animation;
  animation_set_duration( animation,  TIME_SLOT_ANIMATION_DURATION);
  animation_set_curve(    animation,  AnimationCurveLinear);
  animation_set_handlers( animation,  (AnimationHandlers){
    .stopped = (AnimationStoppedHandler)time_slot_slide_in_animation_stopped
  }, (void *)time_slot);

  animation_schedule(animation);
}

void time_slot_slide_in_animation_stopped(Animation *slide_in_animation, bool finished, void *context) {
  TimeSlot *time_slot = (TimeSlot *)context;

  destroy_property_animation(&time_slot->slide_in_animation);

  time_slot->updating = false;
}

void slide_out_digit_image_from_time_slot(TimeSlot *time_slot) {
  int time_image_size = time_slot->slot_size;

  destroy_property_animation(&time_slot->slide_out_animation);

  GRect from_frame = frame_for_time_slot(time_slot);

  int to_x = from_frame.origin.x;
  int to_y = from_frame.origin.y;
  switch (time_slot->slot.number) {
    case 0:
      to_y -= time_image_size + MARGIN;
      break;
    case 1:
      to_x += time_image_size + MARGIN;
      break;
    case 2:
      to_x -= time_image_size + MARGIN;
      break;
    case 3:
      to_y += time_image_size + MARGIN;
      break;
  }
  GRect to_frame = GRect(to_x, to_y, time_image_size, time_image_size);

  BitmapLayer *image_layer = time_slot->slot.image_layer;

  time_slot->slide_out_animation = property_animation_create_layer_frame(bitmap_layer_get_layer(image_layer), &from_frame, &to_frame);

  Animation *animation = (Animation *)time_slot->slide_out_animation;
  animation_set_duration( animation,  TIME_SLOT_ANIMATION_DURATION);
  animation_set_curve(    animation,  AnimationCurveLinear);
  animation_set_handlers(animation, (AnimationHandlers){
    .stopped = (AnimationStoppedHandler)time_slot_slide_out_animation_stopped
  }, (void *)time_slot);

  animation_schedule(animation);
}

void time_slot_slide_out_animation_stopped(Animation *slide_out_animation, bool finished, void *context) {
  TimeSlot *time_slot = (TimeSlot *)context;

  destroy_property_animation(&time_slot->slide_out_animation);

  if (time_slot->new_state == EMPTY_SLOT) {
    time_slot->updating = false;
  }
  else {
    unload_digit_image_from_slot(&time_slot->slot);

    slide_in_digit_image_into_time_slot(time_slot, time_slot->new_state);

    time_slot->new_state = EMPTY_SLOT;
  }
}

// Day
void predisplay_day(){
  destroy_image_item(&day_item);
	
  GRect day_layer_frame = GRect(
    MARGIN, 
    footer_height - DAY_IMAGE_HEIGHT - MARGIN, 
    DAY_IMAGE_WIDTH, 
    DAY_IMAGE_HEIGHT
  );
  day_item.layer = layer_create(day_layer_frame);
  layer_add_child(footer_layer, day_item.layer);  
}

void display_day(struct tm *tick_time) {
  if (settings.lang == 0) {
    load_image_item(&day_item, DAY_IMAGE_RESOURCE_IDS_IT[tick_time->tm_wday]);
  }else if(settings.lang == 1){
    load_image_item(&day_item, DAY_IMAGE_RESOURCE_IDS_EN[tick_time->tm_wday]);
  }
}

// Date
void unload_date_item(){
  for (int i = 0; i < NUMBER_OF_DATE_SLOTS; i++) {
    unload_digit_image_from_slot(&date_slots[i]);
  }
  layer_destroy(date_layer);	
}

void predisplay_date(int format){
  unload_date_item();

  // Offset for date format
  int DATE_OFFSET = 29;
	
  if (format == 1) {
	DATE_OFFSET = 62;
    //unload_image_item(&years_20_item);
  }		
	
  // Date
  for (int i = 0; i < NUMBER_OF_DATE_SLOTS; i++) {
    Slot *date_slot = &date_slots[i];
    date_slot->number = i;
    date_slot->state  = EMPTY_SLOT;
  }

  GRect date_layer_frame = GRectZero;
  date_layer_frame.size.w   = DATE_IMAGE_WIDTH + MARGIN + DATE_IMAGE_WIDTH + DATE_PART_SPACE + DATE_IMAGE_WIDTH + MARGIN + DATE_IMAGE_WIDTH;
  date_layer_frame.size.h   = DATE_IMAGE_HEIGHT;
  date_layer_frame.origin.x = DATE_OFFSET;
  date_layer_frame.origin.y = footer_height - DATE_IMAGE_HEIGHT - MARGIN;

  date_layer = layer_create(date_layer_frame);
  layer_add_child(footer_layer, date_layer);
}

void display_date(struct tm *tick_time) {
  int day   = tick_time->tm_mday;
  /*int month = tick_time->tm_mon + 1;*/

  if(USE_AMERICAN_DATE_FORMAT) {
    /*display_date_value(month, 0);*/
    display_date_value(day,   1);
  }else {
    display_date_value(day,   0);
    /*display_date_value(month, 1);*/
  }
}

void display_date_value(int value, int part_number) {
  value = value % 100; // Maximum of two digits per row.

  for (int column_number = 1; column_number >= 0; column_number--) {
    int date_slot_number = (part_number * 2) + column_number;

    Slot *date_slot = &date_slots[date_slot_number];

    update_date_slot(date_slot, value % 10);

    value = value / 10;
  }
}

void update_date_slot(Slot *date_slot, int digit_value) {
  if (date_slot->state == digit_value)
    return;

  int x = date_slot->number * (DATE_IMAGE_WIDTH + MARGIN);
  if (date_slot->number >= 2) {
    x += 3; // 3 extra pixels of space between the day and month
  }
  GRect frame =  GRect(x, 0, DATE_IMAGE_WIDTH, DATE_IMAGE_HEIGHT);

  unload_digit_image_from_slot(date_slot);
  load_digit_image_into_slot(date_slot, digit_value, date_layer, frame, DATE_IMAGE_RESOURCE_IDS);
}


// Month
void predisplay_month(int format){
  destroy_image_item(&month_item);
	
  int MONTH_OFFSET = 71;		
  if (format == 1) {
  	MONTH_OFFSET = 29;
 	//load_image_item(&years_20_item);
  }
	
  GRect month_layer_frame = GRect(
  	MARGIN + MONTH_OFFSET, 
	footer_height - MONTH_IMAGE_HEIGHT - MARGIN, 
	MONTH_IMAGE_WIDTH, 
	MONTH_IMAGE_HEIGHT
  );
  month_item.layer = layer_create(month_layer_frame);
  layer_add_child(footer_layer, month_item.layer);
}

void display_month(struct tm *tick_time) {
  if (settings.lang == 0) {
    load_image_item(&month_item, MONTH_IMAGE_RESOURCE_IDS_IT[tick_time->tm_mon]);
  }else if(settings.lang == 1){
   load_image_item(&month_item, MONTH_IMAGE_RESOURCE_IDS_EN[tick_time->tm_mon]);
  }
}

// Seconds
/*void display_seconds(struct tm *tick_time) {
  int seconds = tick_time->tm_sec;

  seconds = seconds % 100; // Maximum of two digits per row.

  for (int second_slot_number = 1; second_slot_number >= 0; second_slot_number--) {
    Slot *second_slot = &second_slots[second_slot_number];

    update_second_slot(second_slot, seconds % 10);
    
    seconds = seconds / 10;
  }
}

void update_second_slot(Slot *second_slot, int digit_value) {
  if (second_slot->state == digit_value)
    return;

  GRect frame = GRect(
    second_slot->number * (SECOND_IMAGE_WIDTH + MARGIN), 
    0, 
    SECOND_IMAGE_WIDTH, 
    SECOND_IMAGE_HEIGHT
  );

  unload_digit_image_from_slot(second_slot);
  load_digit_image_into_slot(second_slot, digit_value, seconds_layer, frame, SECOND_IMAGE_RESOURCE_IDS);
}*/

// Years
void display_years(struct tm *tick_time) {
  int years = tick_time->tm_year;

  years = years % 100; // Maximum of two digits per row.

  for (int year_slot_number = 1; year_slot_number >= 0; 
year_slot_number--) {
    Slot *year_slot = &year_slots[year_slot_number];

    update_year_slot(year_slot, years % 10);
    
    years = years / 10;
  }
}

void update_year_slot(Slot *year_slot, int digit_value) {
  if (year_slot->state == digit_value)
    return;

  GRect frame = GRect(
    year_slot->number * (YEAR_IMAGE_WIDTH + MARGIN), 
    0, 
    YEAR_IMAGE_WIDTH, 
    YEAR_IMAGE_HEIGHT
  );

  unload_digit_image_from_slot(year_slot);
  load_digit_image_into_slot(year_slot, digit_value, years_layer, frame, 
YEAR_IMAGE_RESOURCE_IDS);
}

// Handlers
int main(void) {
  init();
  app_event_loop();
  deinit();
}

void in_configuration_handler(DictionaryIterator *received, void *context) {
	time_t now = time(NULL);
	tick_time = localtime(&now);
	
	if (DEBUGLOG) { APP_LOG(APP_LOG_LEVEL_DEBUG, "AppMessage Receive..."); }
	if (DEBUGLOG) { APP_LOG(APP_LOG_LEVEL_DEBUG, "in_configuration_handler"); }
	if (DEBUGLOG) { APP_LOG(APP_LOG_LEVEL_DEBUG, "Current Settings: date_format=%d, ampm_format=%d, lang=%d",
	  settings.date_format,
	  settings.ampm_format,
	  settings.lang
    ); }
	
	Tuple *dictItem;
	
	dictItem = dict_read_first(received);
	
	bool update_month = false;
	if (dictItem != NULL) {
	  int new_format = dictItem->value->uint8;
	  if (DEBUGLOG) { APP_LOG(APP_LOG_LEVEL_DEBUG, "new dateformat: %d", new_format); }
	  
	  if( new_format != settings.date_format){
		settings.date_format = new_format;
		
	    predisplay_date(settings.date_format);
	    display_date(tick_time);
		predisplay_month(settings.date_format);
		
	    update_month = true;
	  }
	}
	dictItem = dict_read_next(received);
	if (dictItem != NULL) {
	  int new_format = dictItem->value->uint8;
	  if (DEBUGLOG) { APP_LOG(APP_LOG_LEVEL_DEBUG, "new ampmformat: %d", new_format); }		
	  
	  if( new_format != settings.ampm_format){
		settings.ampm_format = new_format;		
	  
	    display_time(tick_time);		
	  }
	}
	dictItem = dict_read_next(received);
	if (dictItem != NULL) {
	  int new_lang = dictItem->value->uint8;
	  if (DEBUGLOG) { APP_LOG(APP_LOG_LEVEL_DEBUG, "new lang: %d", new_lang); }		
	  
	  if ( new_lang != settings.lang){
		settings.lang = new_lang;
	  
	    display_day(tick_time);
		
	    update_month = true;
	  }
	}
	if (update_month){
	  display_month(tick_time);	
	}
}

void in_drop_handler(AppMessageResult reason, void *context) {
// incoming message dropped
  if (DEBUGLOG) { app_log(APP_LOG_LEVEL_DEBUG, __FILE__, __LINE__, "AppMessage Dropped: %d", reason); }
}

void my_out_sent_handler(DictionaryIterator *sent, void *context) {
// outgoing message was delivered
	if (DEBUGLOG) { app_log(APP_LOG_LEVEL_DEBUG, __FILE__, __LINE__, "AppMessage Send.."); }
}
void my_out_fail_handler(DictionaryIterator *failed, AppMessageResult reason, void *context) {
// outgoing message failed
  if (DEBUGLOG) { app_log(APP_LOG_LEVEL_DEBUG, __FILE__, __LINE__, "AppMessage Failed to Send: %d", reason); }
}

static void app_message_init(void) {
  // Register message handlers
  app_message_register_inbox_received(in_configuration_handler);
  app_message_register_inbox_dropped(in_drop_handler);
  app_message_register_outbox_sent(my_out_sent_handler);
  app_message_register_outbox_failed(my_out_fail_handler);
  // Init buffers
  app_message_open(app_message_inbox_size_maximum(), app_message_outbox_size_maximum());
  //fetch_msg();
}

void init() {
  if (persist_exists(PK_SETTINGS)) {
    persist_read_data(PK_SETTINGS, &settings, sizeof(settings));
	  if (DEBUGLOG) { APP_LOG(APP_LOG_LEVEL_DEBUG, "persist readed settings"); }
  }
	
  app_message_init();

  window = window_create();
  window_stack_push(window, true /* Animated */);
  window_set_background_color(window, GColorBlack);

  Layer *root_layer = window_get_root_layer(window);

  // Header
  int header_height = TOP_MARGIN;

  header_layer = layer_create(GRect(0, 0, SCREEN_WIDTH, header_height));
  
  // BT
  GRect bt_layer_frame = GRect(
    MARGIN, 
    MARGIN, 
    BT_IMAGE_WIDTH, 
    BT_IMAGE_HEIGHT
  );
  bt_item.layer = layer_create(bt_layer_frame);
  layer_add_child(header_layer, bt_item.layer);
	
  // Logo
  GRect logo_layer_frame = GRect(
    MARGIN + 36, 
    MARGIN + 2, 
    LOGO_IMAGE_WIDTH, 
    LOGO_IMAGE_HEIGHT
  );
  logo_item.layer = layer_create(logo_layer_frame);
  layer_add_child(header_layer, logo_item.layer);
	
  // Battery
  GRect battery_layer_frame = GRect(
    SCREEN_WIDTH - MARGIN - BATTERY_IMAGE_WIDTH, 
    MARGIN, 
    BATTERY_IMAGE_WIDTH, 
    BATTERY_IMAGE_HEIGHT
  );
  battery_item.layer = layer_create(battery_layer_frame);
  layer_add_child(header_layer, battery_item.layer);
  
  layer_add_child(root_layer, header_layer);
	
  // Time
  for (int i = 0; i < NUMBER_OF_TIME_SLOTS; i++) {
    TimeSlot *time_slot = &time_slots[i];
    time_slot->slot.number  = i;
    time_slot->slot.state   = EMPTY_SLOT;
    time_slot->new_state    = EMPTY_SLOT;
    time_slot->updating     = false;
	if(i < 2) {
	  time_slot->slot_size    = TIME_IMAGE_WIDTH_HH;
	}else {
	  time_slot->slot_size    = TIME_IMAGE_WIDTH;
	}
  }

  time_layer = layer_create(GRect(0, 0, SCREEN_WIDTH, SCREEN_WIDTH + 2));
  layer_set_clips(time_layer, true);
	
  // Meridiem
  GRect meridiem_layer_frame = GRect(
    134, 
    50, 
    9, 
    25
  );
  meridiem_item.layer = layer_create(meridiem_layer_frame);
  layer_add_child(time_layer, meridiem_item.layer);
	
  layer_add_child(root_layer, time_layer);
	
  footer_layer = layer_create(GRect(0, SCREEN_WIDTH, SCREEN_WIDTH, footer_height));
	layer_set_clips(footer_layer, true);
  layer_add_child(root_layer, footer_layer);

  predisplay_day();
  predisplay_date(settings.date_format);
  predisplay_month(settings.date_format);

  // Seconds
  /*for (int i = 0; i < NUMBER_OF_SECOND_SLOTS; i++) {
    Slot *second_slot = &second_slots[i];
    second_slot->number = i;
    second_slot->state  = EMPTY_SLOT;
  }

  GRect seconds_layer_frame = GRect(
    SCREEN_WIDTH - SECOND_IMAGE_WIDTH - MARGIN - SECOND_IMAGE_WIDTH - MARGIN, 
    footer_height - SECOND_IMAGE_HEIGHT - MARGIN, 
    SECOND_IMAGE_WIDTH + MARGIN + SECOND_IMAGE_WIDTH, 
    SECOND_IMAGE_HEIGHT
  );
  seconds_layer = layer_create(seconds_layer_frame);
  layer_add_child(footer_layer, seconds_layer);*/
	
  // Years 20XX
  GRect years_20_layer_frame = GRect(
    108, 
	footer_height - YEAR_IMAGE_HEIGHT - MARGIN,
    YEARS_20_IMAGE_WIDTH, 
    YEARS_20_IMAGE_HEIGHT
  );
  years_20_item.layer = layer_create(years_20_layer_frame);
  layer_add_child(footer_layer, years_20_item.layer);

  // Years
  for (int i = 0; i < NUMBER_OF_YEAR_SLOTS; i++) {
    Slot *year_slot = &year_slots[i];
    year_slot->number = i;
    year_slot->state  = EMPTY_SLOT;
  }

  GRect years_layer_frame = GRect(
    SCREEN_WIDTH - YEAR_IMAGE_WIDTH - MARGIN - YEAR_IMAGE_WIDTH - MARGIN, 
    footer_height - YEAR_IMAGE_HEIGHT - MARGIN, 
    YEAR_IMAGE_WIDTH + MARGIN + YEAR_IMAGE_WIDTH, 
    YEAR_IMAGE_HEIGHT
  );
  years_layer = layer_create(years_layer_frame);
  layer_add_child(footer_layer, years_layer);
	
  // Display
  load_image_item(&bt_item, RESOURCE_ID_IMAGE_BT);
  load_image_item(&logo_item, RESOURCE_ID_IMAGE_LOGO);
  display_battery(header_layer);
  
  time_t now = time(NULL);
  tick_time = localtime(&now);
  
  display_time(tick_time);
	
  display_day(tick_time);	
  display_date(tick_time);
  display_month(tick_time);
	
  load_image_item(&years_20_item, RESOURCE_ID_IMAGE_YEARS_20);
  display_years(tick_time);

  tick_timer_service_subscribe(MINUTE_UNIT, handle_tick);
  bluetooth_connection_service_subscribe(handle_bluetooth);
  battery_state_service_subscribe(handle_battery);	
}

void handle_tick(struct tm *tick_time, TimeUnits units_changed) {
  display_time(tick_time);

  if ((units_changed & HOUR_UNIT) == HOUR_UNIT) {
	if(VIBE_ON_HOUR) {
      vibes_double_pulse();
    }
  }
	
  if ((units_changed & DAY_UNIT) == DAY_UNIT) {
    display_day(tick_time);
    display_date(tick_time);
  }
  if ((units_changed & MONTH_UNIT) == DAY_UNIT) {
	display_month(tick_time);
  }
  if ((units_changed & YEAR_UNIT) == DAY_UNIT) {
	display_years(tick_time);
  }
}

void deinit() {
  persist_write_data(PK_SETTINGS, &settings, sizeof(settings));
	if (DEBUGLOG) { APP_LOG(APP_LOG_LEVEL_DEBUG, "persist writed settings"); }
	
  tick_timer_service_unsubscribe();
  bluetooth_connection_service_unsubscribe();
  battery_state_service_unsubscribe();
	
  destroy_image_item(&bt_item);
  destroy_image_item(&logo_item);
	
  unload_battery_item();
	
  layer_destroy(header_layer);

  // Time
  for (int i = 0; i < NUMBER_OF_TIME_SLOTS; i++) {
    unload_digit_image_from_slot(&time_slots[i].slot);

    destroy_property_animation(&time_slots[i].slide_in_animation);
    destroy_property_animation(&time_slots[i].slide_out_animation);
  }
  
  destroy_image_item(&meridiem_item);
	
  layer_destroy(time_layer);

  // Day
  destroy_image_item(&day_item);
  // Date
  unload_date_item();
	
  // Month
  destroy_image_item(&month_item);
  // Seconds
  /*for (int i = 0; i < NUMBER_OF_SECOND_SLOTS; i++) {
    unload_digit_image_from_slot(&second_slots[i]);
  }
  layer_destroy(seconds_layer);*/
	
  // Years
  destroy_image_item(&years_20_item);
  for (int i = 0; i < NUMBER_OF_YEAR_SLOTS; i++) {
    unload_digit_image_from_slot(&year_slots[i]);
  }
  layer_destroy(years_layer);

  layer_destroy(footer_layer);

  window_destroy(window);
}

