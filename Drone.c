/* Konda Nihaal Sekhar 
  ME24B1062 */

  #include<stdio.h>
  #include<stdlib.h>
  #include<string.h>
  
  #define max 6
  
  char* queue[max];
  int front = -1, rear = -1;
  
  char* stack[max];
  int top = -1;
  
  char* arr[max];
  int size = 0;
  
  struct overload_node 
  {
      char name[20];
      struct overload_node* next;
  };
  struct overload_node* overload_head = NULL;
  
  struct service_node 
  {
      char name[20];
      struct service_node *prev, *next;
  };
  struct service_node* service_head = NULL;
  
  struct emergency_node 
  {
      char name[20];
      struct emergency_node *next;
  };
  struct emergency_node* emergency_tail = NULL;
  
  //---------------- Queue Functions -------------------------
  
  void enqueue(char* item) 
  {
      if (rear < max - 1) 
      {
          if (front == -1) front = 0;
          rear++;
          queue[rear] = strdup(item);
      }
  }
  
  char* dequeue() 
  {
      if (front == -1 || front > rear) 
      {
          return NULL;
      }
      char* item = queue[front];
      front++;
      if (front > rear) 
      {
          front = rear = -1;
      }
      return item;
  }
  
  //---------------- Stack Functions ------------------------
  
  void push(char* item) 
  {
      if (top < max - 1) 
      {
          top++;
          stack[top] = strdup(item);
      }
  }
  
  char* pop() 
  {
      if (top >= 0) 
      {
          char* item = stack[top];
          top--;
          return item;
      }
      return NULL;
  }
  
  //---------------- Request Dispatch ------------------------
  
  void request_dispatch() 
  {
      char* requests[] = { "Food", "Medicine", "Tools", "Water", "Parts", "Fuel" };
      printf("\nIncoming Requests to SkyLink Tower:\n");
      printf("----------------------------------------\n");
      for (int i = 0; i < 6; i++) 
      {
          printf("Ground Station Request: %s\n", requests[i]);
          enqueue(requests[i]);
      }
  
      printf("\nPrioritizing Urgent Missions (LIFO Stack):\n");
      printf("----------------------------------------\n");
      for (int i = 0; i < 6; i++) 
      {
          char* item = dequeue();
          if (item != NULL) 
          {
              push(item);
          }
      }
  
      printf("\nDispatch Sequence:\n");
      printf("----------------------------------------\n");
      for (int i = 0; i < 6; i++) 
      {
          char* item = pop();
          if (item != NULL) 
          {
              printf("Dispatching Drone with: %s\n", item);
          }
      }
  }
  
  //---------------- Flight Log (Array as Circular Buffer) ------------------------
  
  void log_delivery(char* delivery) 
  {
      if (size < max) 
      {
          arr[size++] = strdup(delivery);
      } 
      else 
      {
          free(arr[0]); // free old memory
          for (int i = 1; i < max; i++) 
          {
              arr[i - 1] = arr[i];
          }
          arr[max - 1] = strdup(delivery);
      }
  }
  
  void print_flightLog() 
  {
      printf("\nFlight Log Records (Latest 6 Missions):\n");
      printf("----------------------------------------\n");
      for (int i = 0; i < size; i++) 
      {
          printf("%s COMPLETED\n", arr[i]);
      }
  }
  
  //---------------- Overload Management (Singly Linked List) ------------------------
  
  void insert_overload(char* name) 
  {
      struct overload_node* node = (struct overload_node*)malloc(sizeof(struct overload_node));
      strcpy(node->name, name);
      node->next = overload_head;
      overload_head = node;
      printf("%s Reported Overloaded\n", name);
  }
  
  void remove_overload(char* name) 
  {
      struct overload_node* curr = overload_head;
      struct overload_node* prev = NULL;
  
      while (curr != NULL && strcmp(curr->name, name) != 0) 
      {
          prev = curr;
          curr = curr->next;
      }
  
      if (curr == NULL) 
      {
          return;
      }
  
      if (prev == NULL) 
      {
          overload_head = curr->next;
      } 

      else 
      {
          prev->next = curr->next;
      }
  
      free(curr);
      printf("%s SERVICED\n", name);
  }
  
  //---------------- Diagnostic History (Doubly Linked List) ------------------------
  
  void insert_service(char* name) 
  {
      struct service_node* node = (struct service_node*)malloc(sizeof(struct service_node));
      strcpy(node->name, name);
      node->prev = NULL;
      node->next = service_head;
  
      if (service_head != NULL) 
      {
          service_head->prev = node;
      }
      service_head = node;
  }
  
  void traverse_service() 
  {
      struct service_node* temp = service_head;
  
      printf("\nForward Diagnostic History:\n");
      printf("----------------------------------------\n");
      while (temp != NULL) 
      {
          printf("%s Checked\n", temp->name);
          if (temp->next == NULL) break;
          temp = temp->next;
      }
  
      printf("\nReverse Report Review:\n");
      printf("----------------------------------------\n");
      while (temp != NULL) 
      {
          printf("%s RECHECKED\n", temp->name);
          temp = temp->prev;
      }
  }
  
  //---------------- Emergency Reroute (Circular Linked List) ------------------------
  
  void insert_emergency(char* name) 
  {
      struct emergency_node* node = (struct emergency_node*)malloc(sizeof(struct emergency_node));
      strcpy(node->name, name);
  
      if (emergency_tail == NULL) 
      {
          node->next = node;
          emergency_tail = node;
      } 
      else 
      {
          node->next = emergency_tail->next;
          emergency_tail->next = node;
          emergency_tail = node;
      }
  
      printf("Emergency Reroute Activated: %s\n", name);
  }
  
  void traverse_emergency(int rounds) 
  {
      if (emergency_tail == NULL) return;
  
      struct emergency_node* temp = emergency_tail->next;
      printf("\nEmergency Drone Loop:\n");
      printf("----------------------------------------\n");
  
      for (int i = 0; i < rounds * 2; i++) 
      {
          printf("%s REROUTING\n", temp->name);
          temp = temp->next;
      }
  }
  
  //---------------- Main Function ------------------------
  
  void main() 
  {
    printf("=== SKYLINK: CARGO DRONE COMMAND CENTER ===\n");

    request_dispatch();

    printf("\n----------------------------------------\n");

    char* deliveries[] = { "Del1", "Del2", "Del3", "Del4", "Del5", "Del6", "Del7", "Del8" };
    for (int i = 0; i < 8; i++) 
    {
        log_delivery(deliveries[i]);
    }

    print_flightLog();

    printf("\n----------------------------------------\n");

    insert_overload("Drone3");
    insert_overload("Drone6");
    remove_overload("Drone3");

    printf("\n----------------------------------------\n");

    insert_service("Drone3");
    traverse_service();

    printf("\n----------------------------------------\n");

    insert_emergency("Drone1");
    insert_emergency("Drone4");
    traverse_emergency(2);

    printf("\n----------------------------------------\n");
    printf("Mission Status: All systems operational.\n");
  
  }
  