//modify and submit this file only
#include "pa3.h"
#include <iostream>
using namespace std;
//you are NOT allowed to include any additional library; see FAQ

//helper_function
int car_length(const TrainCar* head){
  int length = 0;
  for(const TrainCar* p = head; p != nullptr; p = p->next){
    ++length;
  }
  return length;
}

//helper_function
TrainCar* add_divideCar(TrainCar* head, int position, CarType type, int maxLoad, int load)
{
  TrainCar* new_car = new TrainCar; //create new node
  new_car->type = type; //create type
  new_car->maxLoad = maxLoad; //create maxLoad
  new_car->load = load; //create load
  new_car->next = nullptr;
  int length;
  length = car_length(head); //find length
  //base case
  if(type == HEAD || position <= 0 || position > length || maxLoad <= 0 || head == nullptr){
    return 0;
  }

  //point the prev car
  TrainCar* prev_car = head;
  //int num = 1;
  for(int num = 0; num < position-1 && prev_car->next != nullptr; prev_car = prev_car->next, ++num);

  //insert to the end
  if(position == length){
    
    prev_car->next = new_car;
    new_car->prev = prev_car;
  }
  //insert into middle
  if(position < length){

    new_car->next = prev_car->next;
    prev_car->next = new_car;
    new_car->prev = prev_car;
    new_car->next->prev = new_car;

  }
  return head;
}

//helper_function

TrainCar* createTrainHead()
{ 
  TrainCar* head = new TrainCar;
  head->type = HEAD;
  head->maxLoad = 0;
  head->load = 0;
  head->prev = nullptr;
  head->next = nullptr;
  return head;
}

bool addCar(TrainCar* head, int position, CarType type, int maxLoad)
{
  int length;
  length = car_length(head); //find length

  //base case
  if(type == HEAD || position <= 0 || position > length || maxLoad <= 0 || head == nullptr){
    return 0;
  }

  TrainCar* new_car = new TrainCar; //create new node
  new_car->type = type; //create type
  new_car->maxLoad = maxLoad; //create maxLoad
  new_car->load = 0; //create load
  new_car->next = nullptr;
  
  //point the prev car
  TrainCar* prev_car = head;
  //int num = 1;
  for(int num = 0; num < position-1 && prev_car->next != nullptr; prev_car = prev_car->next, ++num);

  //insert to the end
  if(position == length){ 
    prev_car->next = new_car;
    new_car->prev = prev_car;
  }
  //insert into middle
  if(position < length){

    new_car->next = prev_car->next;
    prev_car->next = new_car;
    new_car->prev = prev_car;
    new_car->next->prev = new_car;

  }
  return 1;
}

bool deleteCar(TrainCar* head, int position)
{
  int length;
  length = car_length(head); //find length
  //base case
  if(position < 1 || position >= length || head == nullptr){
    return 0;
  }
  TrainCar* prev = nullptr;
  TrainCar* current = head;

  //pointer prev and current
  int num = 0;
  while (current != nullptr && num != position){
    prev = current;
    current = current->next;
    ++num;
  }
  //del middle
  if(current->next != nullptr){
    prev->next = current->next;
    prev->next->prev = prev;
  }
  //del end
  else{
    prev->next = nullptr;
  }
  delete current;
  return 1;
}

bool swapCar(TrainCar* head, int a, int b)
{

  int length;
  length = car_length(head); //find length
  //cout<<"length: "<<length<<endl;
  if(a < 1 || a > length-1 || b < 1 || b > length-1 || head == nullptr){
    return 0;
  }  

  if(a>b){
    int temp = a;
    a = b;
    b = temp;
  }
  
  int num_a = 0 , num_b = 0;

  TrainCar* current_a = head;
  while(current_a != nullptr && num_a != a){
    current_a = current_a->next;
    ++num_a;
  }
  //cout<<"added a pointer: "<< num_a <<endl;

  TrainCar* current_b = head;
  while(current_b != nullptr && num_b != b){
    current_b = current_b->next;
    ++num_b;
  }  
  //cout<<"added b pointer: "<< num_b <<endl;

  current_a->prev->next = current_b;

  if(current_b->next != nullptr){
  current_b->next->prev = current_a;
  }

  //node of after_a & before_b
  if(!(current_a->next == current_b && current_b->prev == current_a)){
    current_a->next->prev = current_b;
    current_b->prev->next = current_a;
  }

  TrainCar* temp = current_a->prev;
  if(current_b->prev == current_a){
    current_a->prev = current_b;
  }
  else{
    current_a->prev = current_b->prev;
  }
  current_b->prev = temp;

  temp = current_b->next;    
  if(current_a->next == current_b){
    current_b->next = current_a;
  }
  else{
    current_b->next = current_a->next;
  }
  current_a->next = temp;

  return 1;
}

void sortTrain(TrainCar* head, bool ascending)
{
  if (head == nullptr || head->next == nullptr)
    return ;
  
  bool swapped;
  do{
    int i = 1;
    swapped = false;
    //current = head if(descending) error(core dump)
    for(TrainCar* current = head->next; current->next != nullptr; current = current->next){
      if(ascending){
        if(current->load > current->next->load){
          swapCar(head, i,i+1);
          current = current->prev;
          swapped = true;
        }   
      }
      else{
        if(current->load < current->next->load){
          swapCar(head, i,i+1);
          current = current->prev;
          swapped = true;
        }   
      }      
  
      i++;
      // cout<<"i: "<<i<<endl;
    }
    // cout<<"swapped: "<<swapped<<endl;
  }
  while(swapped);

}

bool load(TrainCar* head, CarType type, int amount)
{
  int freespace = 0;
  TrainCar* current = head->next;

  while(current != nullptr){    
    if(current->type == type){
      freespace += current->maxLoad - current->load;
    } 
    current = current->next;
  }

  if(amount > freespace){
    return 0;
  }
  
  int carspace = 0;
  current = head->next;
  while(current != nullptr){
    
    if(current->type == type){
      carspace = current->maxLoad - current->load;
      if(amount > carspace){
        current->load += carspace;
        amount -= carspace;
      }
      else{
        current->load += amount;
        amount = 0;
      }
    }
    current = current->next;
  }
  return 1;
}

bool unload(TrainCar* head, CarType type, int amount)
{
  int total_load = 0;
  TrainCar* current = head;

  while(current->next != nullptr){
    current = current->next;    
    if(current->type == type){
      total_load += current->load;
    }   
  }

  if(amount > total_load){
    return 0;
  }

  while(current != nullptr){    
    if(current->type == type){
      if(amount > current->load){       
        amount -= current->load;
        current->load = 0;
      }
      else{
        current->load -= amount;
        amount = 0;
      }
    }
    current = current->prev;
  }
  return 1;
}

void printCargoStats(const TrainCar* head)
{ 
  const char enumToStringMapping[6][8] = {"HEAD", "OIL", "COAL", "WOOD", "STEEL", "SUGAR"};
  bool oil_check = 1, coal_check = 1, wood_check = 1, steel_check = 1, sugar_check = 1;
  int total_oil_load = 0, total_coal_load = 0, total_wood_load = 0, total_steel_load = 0, total_sugar_load = 0;
  int total_oil_maxLoad = 0, total_coal_maxLoad = 0, total_wood_maxLoad = 0, total_steel_maxLoad = 0, total_sugar_maxLoad = 0;

  TrainCar* current = head->next;


  while(current != nullptr){       
    if(current->type == OIL){
      total_oil_load += current->load;
      total_oil_maxLoad += current->maxLoad;
      // cout<<"total_oil_load"<<total_oil_load<<endl;
    }  
     if(current->type == COAL){
      total_coal_load += current->load;
      total_coal_maxLoad += current->maxLoad;
      // cout<<"total_coal_load: "<<total_coal_load<<endl;
    }  
    if(current->type == WOOD){
      total_wood_load += current->load;
      total_wood_maxLoad += current->maxLoad;
      // cout<<"total_wood_load: "<<total_wood_load<<endl;
    }  
    if(current->type == STEEL){
      total_steel_load += current->load;
      total_steel_maxLoad += current->maxLoad;
      // cout<<"total_steel_load: "<<total_steel_load<<endl;
    }  
    if(current->type == SUGAR){
      total_sugar_load += current->load;
      total_sugar_maxLoad += current->maxLoad;
      // cout<<"total_sugar_load: "<<total_sugar_load<<endl;
    }  
    current = current->next;
  }

  int type_num = 0, repeat_num = 0;
  current = head->next;
  while(current != nullptr){    
    for(TrainCar* next_car = current -> next; next_car;next_car = next_car -> next){
      if(next_car->type == current->type){
        repeat_num++;
      }
    }
    type_num++;  
    current = current->next;
  }
  // cout<<"repeat_num: "<<repeat_num<<endl;
  type_num -= repeat_num;
  // cout<<"type_num: "<<type_num<<endl;

  int count = 1;
  current = head->next;
  while(current->next != nullptr){       
    if(current->type == OIL){
      if(oil_check){
        cout << enumToStringMapping[current->type];
        cout <<":" <<total_oil_load<<"/"<<total_oil_maxLoad;
        if(count < type_num){
         cout<<",";
       }
        else cout<<endl;
        oil_check = 0;
      }       
    }
  
    if(current->type == COAL){
      if(coal_check){
        cout << enumToStringMapping[current->type];
        cout <<":" <<total_coal_load<<"/"<<total_coal_maxLoad;
        if(count < type_num){
          cout<<",";
        }
        else cout<<endl;
        coal_check = 0;
      }
    }  
    if(current->type == WOOD){
      if(wood_check){
        cout << enumToStringMapping[current->type];
        cout <<":" <<total_wood_load<<"/"<<total_wood_maxLoad;
        if(count < type_num){
          cout<<",";
        }
        else cout<<endl;
        wood_check = 0;
      }

    }  
    if(current->type == STEEL){
      if(steel_check){
        cout << enumToStringMapping[current->type];
        cout <<":" <<total_steel_load<<"/"<<total_steel_maxLoad;
        if(count < type_num){
          cout<<",";
        }  
        else cout<<endl;
        steel_check = 0;
      }
    }
    if(current->type == SUGAR){
      if(sugar_check){
        cout << enumToStringMapping[current->type];
        cout <<":" <<total_sugar_load<<"/"<<total_sugar_maxLoad;
        if(count < type_num){
          cout<<",";
        }  
        else cout<<endl;
        sugar_check = 0;
      }
    }
  count++;
  current = current->next;
  }
}

void divide(const TrainCar* head,  TrainCar* results[CARGO_TYPE_COUNT])
{
  bool oil_check = 1, coal_check = 1, wood_check = 1, steel_check = 1,    sugar_check = 1;
  int length;
  length = car_length(head); //find length

  TrainCar* current = head->next;
  for(int i = 0; i < CARGO_TYPE_COUNT; i++){
    results[i] = nullptr;
  }

  int car_arr[CARGO_TYPE_COUNT]={};
  int cart = 0;
  //check car type num
  while(current != nullptr){       
    if(current->type == OIL){
      if(oil_check){
        car_arr[0] = cart;
        // cout<< "oil_cart" << cart <<endl;
        results[cart] = createTrainHead();
        oil_check = 0;
      }       
    }
  
    if(current->type == COAL){
      if(coal_check){
        car_arr[1] = cart;
        // cout<< "coal_cart" << cart <<endl;
        results[cart] = createTrainHead();
        coal_check = 0;
      }
    }  
    if(current->type == WOOD){
      if(wood_check){
        car_arr[2] = cart;
        // cout<< "wood_cart" << cart <<endl;
        results[cart] = createTrainHead();
        wood_check = 0;
      }

    }  
    if(current->type == STEEL){
      if(steel_check){
        car_arr[3] = cart;
        // cout<< "steel_cart" << cart <<endl;
        results[cart] = createTrainHead();
        steel_check = 0;
      }
    }
    if(current->type == SUGAR){
      if(sugar_check){
        car_arr[4] = cart;
        // cout<< "surgar_cart" << cart <<endl;
        results[cart] = createTrainHead();
        sugar_check = 0;
      }
    }
  ++cart;
  current = current->next;
  }
  
  current = head->next;

  int oil_position = 1, coal_position = 1, wood_position = 1, steel_position = 1, sugar_position = 1;
  
  while(current != nullptr ){ 

    if(current->type == OIL){
      

      results[car_arr[0]] = add_divideCar(results[car_arr[0]], oil_position, OIL, current->maxLoad, current->load);
      // results[car_arr[0]] = results[car_arr[0]]->next;
      oil_position++;
      // cout<<"oil_p:"<<oil_position<<endl;
    }
  
    if(current->type == COAL){
      
      //current->prev = results[cart];
      results[car_arr[1]] = add_divideCar(results[car_arr[1]], coal_position, COAL, current->maxLoad, current->load);
      coal_position++;
      // cout<<"coal_p:"<<coal_position<<endl;
    }  

    if(current->type == WOOD){
      
      results[car_arr[2]] = add_divideCar(results[car_arr[2]], wood_position, WOOD, current->maxLoad, current->load);
      wood_position++;
      // cout<<"wood_p:"<<wood_position<<endl;
    }  
    if(current->type == STEEL){
 
      results[car_arr[3]] = add_divideCar(results[car_arr[3]], steel_position, STEEL, current->maxLoad, current->load);
      steel_position++;
      // cout<<"steel_p:"<<steel_position<<endl;
    }
    if(current->type == SUGAR){

      results[car_arr[4]] = add_divideCar(results[car_arr[4]], sugar_position, SUGAR, current->maxLoad, current->load);
      sugar_position++;
      // cout<<"sugar_p:"<<sugar_position<<endl;
    }
  // position++;
  current = current->next;
  }
}

TrainCar* optimizeForMaximumPossibleCargos(const TrainCar* head, int upperBound)
{
  int length = 0;
  length = car_length(head); //find length
  //cout<<"length: "<<length<<endl;
  int set_size = length-1;
  
  int powerset_size = 1;
  // cout<<"set_size: "<<set_size<<endl;
 
  
  for(int i=0;i < set_size ;i++){
     powerset_size *= 2;
  }
  // cout<<"powerset_size: " <<powerset_size<<endl;

  TrainCar* car_arr[length];
  TrainCar* final_car_arr[length];

  int temp = 0;
  int new_length = 0;
  for (int count = 0; count < powerset_size; count++){
    TrainCar* current = head->next;
    int total_load = 0;
    int temp_length = 0;
    int i =0;
    for(int j = 0; j < set_size+1 && current != nullptr; j++){
      if(count & (1 << j)){
        car_arr[i] = current;
        // cout<<"current-load: "<<current->load<<endl;
        total_load += current->load;
        temp_length++;
        // cout<<"i: "<<i<<endl;
        i++;
      }
      current = current->next;
      // cout<<"***end of j loop***"<<endl;
      // cout<<"temp_length: "<<temp_length<<endl;
    }
    if(total_load > temp && total_load <= upperBound){
      for(int i=0; i <temp_length; i++){
        final_car_arr[i] = car_arr[i];
        // cout<<"final_car_arr[i]->load: "<<final_car_arr[i]->load<<endl;
        new_length = temp_length;
      }
      temp = total_load;
      // cout<<"temp: "<<temp<<endl;
    }
    
    // cout<<"total_load: "<<total_load<<endl;
    // cout<<"-----------count: "<<count<<endl;
  }   

  TrainCar* result_car = createTrainHead();
  // cout<<"-------temp: "<<temp<<endl;
  // cout<<"new_length: "<<new_length<<endl;

  for(int i=0; i <new_length; i++){
    // cout<<"====final_car_arr[i]->load: "<<final_car_arr[i]->load<<endl;
    result_car = add_divideCar(result_car, i+1, final_car_arr[i]->type, final_car_arr[i]->maxLoad, final_car_arr[i]->load);
      }
  return result_car;
}

void deallocateTrain(TrainCar* head)
{
  if(head == nullptr){
    //cout<<"head==nullptr"<<endl;
    return;
  }
  deallocateTrain(head->next);
  //cout<<"del: "<< head->type <<endl;
  delete head;
  head = nullptr;
}

