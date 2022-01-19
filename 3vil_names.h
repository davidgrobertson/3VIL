/* Names of the various functions, including equivalent permutations. */

#define NUM_I_PERMS 6
#define NUM_F_PERMS 6
#define NUM_E_PERMS 24
#define NUM_G_PERMS 8

const char *iname[NUM_I_FUNCS][NUM_I_PERMS] = {
  {"Iuvx", "Ixuv", "Ivxu", "Ivux", "Ixvu", "Iuxv"}, 
  {"Ixyz", "Izxy", "Iyzx", "Iyxz", "Izyx", "Ixzy"}, 
  {"Iuxy", "Iyux", "Ixyu", "Ixuy", "Iyxu", "Iuyx"}, 
  {"Ivxz", "Izvx", "Ixzv", "Ixvz", "Izxv", "Ivzx"}, 
  {"Iuwz", "Izuw", "Iwzu", "Iwuz", "Izwu", "Iuzw"}, 
  {"Ivwy", "Iyvw", "Iwyv", "Iwvy", "Iywv", "Ivyw"}, 
  {"Iuwy", "Iyuw", "Iwyu", "Iwuy", "Iywu", "Iuyw"}, 
  {"Ivwz", "Izvw", "Iwzv", "Iwvz", "Izwv", "Ivzw"}, 
  {"Ivyz", "Izvy", "Iyzv", "Iyvz", "Izyv", "Ivzy"}, 
  {"Iwxy", "Iywx", "Ixyw", "Ixwy", "Iyxw", "Iwyx"}, 
  {"Iuvz", "Izuv", "Ivzu", "Ivuz", "Izvu", "Iuzv"}, 
  {"Iuwx", "Ixuw", "Iwxu", "Iwux", "Ixwu", "Iuxw"}, 
  {"Iuyz", "Izuy", "Iyzu", "Iyuz", "Izyu", "Iuzy"}, 
  {"Iwxz", "Izwx", "Ixzw", "Ixwz", "Izxw", "Iwzx"}, 
  {"Iuvy", "Iyuv", "Ivyu", "Ivuy", "Iyvu", "Iuyv"}, 
  {"Ivwx", "Ixvw", "Iwxv", "Iwvx", "Ixwv", "Ivxw"}
};


/* Template: */
/* "I123", "I312", "I231", "I213", "I321", "I132",  */

/* const char *iname[NUM_I_FUNCS] = {"Iuvx", "Ixyz", "Iuxy", "Ivxz", */
/* 				  "Iuwz", "Ivwy", "Iuwy", "Ivwz", */
/* 				  "Ivyz", "Iwxy", "Iuvz", "Iuwx", */
/* 				  "Iuyz", "Iwxz", "Iuvy", "Ivwx"}; */

const char *fbarname[NUM_F_FUNCS][NUM_F_PERMS] = {
  {"FBARwuxy", "FBARwyux", "FBARwxyu", "FBARwxuy", "FBARwyxu", "FBARwuyx"},
  {"FBARwvxz", "FBARwzvx", "FBARwxzv", "FBARwxvz", "FBARwzxv", "FBARwvzx"},
  {"FBARxuwy", "FBARxyuw", "FBARxwyu", "FBARxwuy", "FBARxywu", "FBARxuyw"},
  {"FBARxvwz", "FBARxzvw", "FBARxwzv", "FBARxwvz", "FBARxzwv", "FBARxvzw"},
  {"FBARuvyz", "FBARuzvy", "FBARuyzv", "FBARuyvz", "FBARuzyv", "FBARuvzy"},
  {"FBARuwxy", "FBARuywx", "FBARuxyw", "FBARuxwy", "FBARuyxw", "FBARuwyx"},
  {"FBARyuvz", "FBARyzuv", "FBARyvzu", "FBARyvuz", "FBARyzvu", "FBARyuzv"},
  {"FBARyuwx", "FBARyxuw", "FBARywxu", "FBARywux", "FBARyxwu", "FBARyuxw"},
  {"FBARvuyz", "FBARvzuy", "FBARvyzu", "FBARvyuz", "FBARvzyu", "FBARvuzy"},
  {"FBARvwxz", "FBARvzwx", "FBARvxzw", "FBARvxwz", "FBARvzxw", "FBARvwzx"},
  {"FBARzuvy", "FBARzyuv", "FBARzvyu", "FBARzvuy", "FBARzyvu", "FBARzuyv"},
  {"FBARzvwx", "FBARzxvw", "FBARzwxv", "FBARzwvx", "FBARzxwv", "FBARzvxw"}
};

/* Template: */
/* "FBAR1234", "FBAR1423", "FBAR1342", "FBAR1324", "FBAR1432", "FBAR1243", */

/* const char *fbarname[NUM_F_FUNCS] = {"FBARwuxy", "FBARwvxz", "FBARxuwy", "FBARxvwz", */
/* 				     "FBARuvyz", "FBARuwxy", "FBARyuvz", "FBARyuwx", */
/* 				     "FBARvuyz", "FBARvwxz", "FBARzuvy", "FBARzvwx"}; */

const char *fname[NUM_F_FUNCS][NUM_F_PERMS] = {
  {"Fwuxy", "Fwyux", "Fwxyu", "Fwxuy", "Fwyxu", "Fwuyx"},
  {"Fwvxz", "Fwzvx", "Fwxzv", "Fwxvz", "Fwzxv", "Fwvzx"},
  {"Fxuwy", "Fxyuw", "Fxwyu", "Fxwuy", "Fxywu", "Fxuyw"},
  {"Fxvwz", "Fxzvw", "Fxwzv", "Fxwvz", "Fxzwv", "Fxvzw"},
  {"Fuvyz", "Fuzvy", "Fuyzv", "Fuyvz", "Fuzyv", "Fuvzy"},
  {"Fuwxy", "Fuywx", "Fuxyw", "Fuxwy", "Fuyxw", "Fuwyx"},
  {"Fyuvz", "Fyzuv", "Fyvzu", "Fyvuz", "Fyzvu", "Fyuzv"},
  {"Fyuwx", "Fyxuw", "Fywxu", "Fywux", "Fyxwu", "Fyuxw"},
  {"Fvuyz", "Fvzuy", "Fvyzu", "Fvyuz", "Fvzyu", "Fvuzy"},
  {"Fvwxz", "Fvzwx", "Fvxzw", "Fvxwz", "Fvzxw", "Fvwzx"},
  {"Fzuvy", "Fzyuv", "Fzvyu", "Fzvuy", "Fzyvu", "Fzuyv"},
  {"Fzvwx", "Fzxvw", "Fzwxv", "Fzwvx", "Fzxwv", "Fzvxw"}
};

/* const char *fname[NUM_F_FUNCS] = {"Fwuxy", "Fwvxz", "Fxuwy", "Fxvwz", */
/* 				  "Fuvyz", "Fuwxy", "Fyuvz", "Fyuwx", */
/* 				  "Fvuyz", "Fvwxz", "Fzuvy", "Fzvwx"}; */


const char *ename[NUM_E_FUNCS][NUM_E_PERMS] = {
  {"Ewuxy", "Ewyux", "Ewxyu", "Ewxuy", "Ewyxu", "Ewuyx",
   "Exuwy", "Exyuw", "Exwyu", "Exwuy", "Exywu", "Exuyw",
   "Euwxy", "Euywx", "Euxyw", "Euxwy", "Euyxw", "Euwyx",
   "Eyuwx", "Eyxuw", "Eywxu", "Eywux", "Eyxwu", "Eyuxw"},
  {"Evwxz", "Evzwx", "Evxzw", "Evxwz", "Evzxw", "Evwzx",
   "Ewvxz", "Ewzvx", "Ewxzv", "Ewxvz", "Ewzxv", "Ewvzx",
   "Exvwz", "Exzvw", "Exwzv", "Exwvz", "Exzwv", "Exvzw",
   "Ezvwx", "Ezxvw", "Ezwxv", "Ezwvx", "Ezxwv", "Ezvxw"},
  {"Euvyz", "Euzvy", "Euyzv", "Euyvz", "Euzyv", "Euvzy",
   "Eyuvz", "Eyzuv", "Eyvzu", "Eyvuz", "Eyzvu", "Eyuzv",
   "Evuyz", "Evzuy", "Evyzu", "Evyuz", "Evzyu", "Evuzy",
   "Ezuvy", "Ezyuv", "Ezvyu", "Ezvuy", "Ezyvu", "Ezuyv"}
};

const char *gname[NUM_G_FUNCS][NUM_G_PERMS] = {
  {"Gwuzvy", "Gwzuvy", "Gwuzyv", "Gwzuyv", "Gwvyuz", "Gwyvuz", "Gwvyzu", "Gwyvzu"},
  {"Gxuvyz", "Gxvuyz", "Gxuvzy", "Gxvuzy", "Gxyzuv", "Gxzyuv", "Gxyzvu", "Gxzyvu"},
  {"Guvxwz", "Guxvwz", "Guvxzw", "Guxvzw", "Guwzvx", "Guzwvx", "Guwzxv", "Guzwxv"},
  {"Gyvwxz", "Gywvxz", "Gyvwzx", "Gywvzx", "Gyxzvw", "Gyzxvw", "Gyxzwv", "Gyzxwv"},
  {"Gvuxwy", "Gvxuwy", "Gvuxyw", "Gvxuyw", "Gvwyux", "Gvywux", "Gvwyxu", "Gvywxu"},
  {"Gzuwxy", "Gzwuxy", "Gzuwyx", "Gzwuyx", "Gzxyuw", "Gzyxuw", "Gzxywu", "Gzyxwu"}
};


/* Template: */
/* {"G12345", "G13245", "G12354", "G13254", "G14523", "G15423", "G14532", "G15432"}, */

/* const char *gname[NUM_G_FUNCS] = {"Gwuzvy", "Gxuvyz", "Guvxwz", */
/* 				  "Gyvwxz", "Gvuxwy", "Gzuwxy"}; */
