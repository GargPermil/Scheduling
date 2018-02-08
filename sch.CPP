#include <iostream>
#include<time.h>
#include<stdlib.h>

using namespace std;

struct PROCESS {
    int id;
    int arrival_time;
    int burst_time;
    int remaining_burst_time;
    int waiting_time;
    int last_quantum;
    int turn_around_time;
    struct PROCESS *next;
};

struct PROCESS *newNode(int arrival_time, int burst_time){
    static int id=0;
    struct PROCESS * tmp = new PROCESS;
    tmp->id=++id;
    tmp->arrival_time=arrival_time;
    tmp->burst_time = burst_time;
    tmp->remaining_burst_time = 0;
    tmp->waiting_time = 0;
    tmp->last_quantum=0;
    tmp->turn_around_time=0;
    tmp->next=NULL;
    return tmp;
};

struct PROCESS *copyNode(struct PROCESS *node){
    struct PROCESS * tmp = new PROCESS;
    tmp->id=node->id;
    tmp->arrival_time=node->arrival_time;
    tmp->burst_time = node->burst_time;
    tmp->remaining_burst_time = node->remaining_burst_time;
    tmp->waiting_time = node->waiting_time;
    tmp->last_quantum=node->last_quantum;
    tmp->turn_around_time=node->turn_around_time;
    tmp->next=NULL;
    return tmp;
}

void insert_process(struct PROCESS **processes, struct PROCESS *node){
    if(node!=NULL){
        if(*processes==NULL)
            *processes=node;
        else{
            node->next = *processes;
            *processes=node;
        }
    }
}

void insert_process_end(struct PROCESS **processes, struct PROCESS *node){
    if(node!=NULL){
        if(*processes==NULL)
            *processes=node;
        else{
            struct PROCESS *cur = *processes;
            while(cur->next!=NULL)
                cur=cur->next;
            cur->next=node;
            node->next=NULL;
        }
    }
}

void insert_process_arrival_time(struct PROCESS **processes, struct PROCESS *node){
    if(node!=NULL){
        if(*processes==NULL)
            *processes=node;
        else{
            if((*processes)->arrival_time>node->arrival_time){
                node->next = *processes;
                *processes=node;
            } else {
                struct PROCESS *cur=*processes;
                while(cur->next!=NULL && cur->next->arrival_time<node->arrival_time)
                    cur=cur->next;
                node->next=cur->next;
                cur->next=node;
            }
        }
    }
}

void insert_process_burst_time(struct PROCESS **processes, struct PROCESS *node){
    if(node!=NULL){
        if(*processes==NULL)
            *processes=node;
        else{
            if((*processes)->burst_time>node->burst_time){
                node->next = *processes;
                *processes=node;
            } else {
                struct PROCESS *cur=*processes;
                while(cur->next!=NULL && cur->next->burst_time<node->burst_time)
                    cur=cur->next;
                node->next=cur->next;
                cur->next=node;
            }
        }
    }
}

void insert_process_remaining_burst_time(struct PROCESS **processes, struct PROCESS *node){
    if(node!=NULL){
        if(*processes==NULL)
            *processes=node;
        else{
            if((*processes)->remaining_burst_time>node->remaining_burst_time){
                node->next = *processes;
                *processes=node;
            } else {
                struct PROCESS *cur=*processes;
                while(cur->next!=NULL && cur->next->remaining_burst_time<node->remaining_burst_time)
                    cur=cur->next;
                node->next=cur->next;
                cur->next=node;
            }
        }
    }
}

void insert_process_pid(struct PROCESS **processes, struct PROCESS *node){
    if(node!=NULL){
        if(*processes==NULL)
            *processes=node;
        else{
            if((*processes)->id>node->id){
                node->next = *processes;
                *processes=node;
            } else {
                struct PROCESS *cur=*processes;
                while(cur->next!=NULL && cur->next->id<node->id)
                    cur=cur->next;
                node->next=cur->next;
                cur->next=node;
            }
        }
    }
}

void delete_process(struct PROCESS **processes){
    if(*processes!=NULL){
        struct PROCESS *tmp=*processes;
        *processes = (*processes)->next;
        delete tmp;
    }
}

void sortBy_arrival_time(struct PROCESS **processes){
    struct PROCESS *cur=*processes,*nextnode, *newhead=NULL;
    while(cur!=NULL){
        nextnode=cur->next;
        cur->next=NULL;
        insert_process_arrival_time(&newhead,cur);
        cur=nextnode;
    }
    *processes=newhead;
}

void sortBy_pid(struct PROCESS **processes){
    struct PROCESS *cur=*processes,*nextnode, *newhead=NULL;
    while(cur!=NULL){
        nextnode=cur->next;
        cur->next=NULL;
        insert_process_pid(&newhead,cur);
        cur=nextnode;
    }
    *processes=newhead;
}

void sortBy_burst_time(struct PROCESS **processes){
    struct PROCESS *cur=*processes,*nextnode, *newhead=NULL;
    while(cur!=NULL){
        nextnode=cur->next;
        cur->next=NULL;
        insert_process_burst_time(&newhead,cur);
        cur=nextnode;
    }
    *processes=newhead;
}

struct PROCESS *find_process_node(struct PROCESS *processes, int pid){
    struct PROCESS *cur=processes;
    while(cur!=NULL){
        if(cur->id==pid)
            return cur;
        cur=cur->next;
    }
    return NULL;
}

void generate_process(struct PROCESS **processes){
    int no_of_process,i;
    int MAX_PROCESS_BURST_TIME;
    cout << "Enter no of process : " ;
    cin >> no_of_process;
    cout << "Enter maximum burst time [Minimum = 20]: " ;
    cin >> MAX_PROCESS_BURST_TIME;
    if(MAX_PROCESS_BURST_TIME<20)
        MAX_PROCESS_BURST_TIME=20;
    srand(time(0));
    for(i=0;i<no_of_process;i++){
        int _at,_bt,_max_arrival_time;
        _max_arrival_time = (no_of_process * MAX_PROCESS_BURST_TIME)/3;
        _at=rand()%_max_arrival_time;
        _bt=rand()% MAX_PROCESS_BURST_TIME;
        if(_bt==0)
            _bt++;
        struct PROCESS *tmp = newNode(_at,_bt);
        insert_process(processes,tmp);
    }
}

void display_process(struct PROCESS *processes){
    struct PROCESS *cur=processes;
    cout << "Process" << endl;
    cout << "PID\tAT\tBT\tWT\tTAT"<<endl;
    while(cur!=NULL){
        cout << cur->id << "\t";
        cout << cur->arrival_time << "\t";
        cout << cur->burst_time << "\t";
        cout << cur->waiting_time << "\t";
        cout << cur->turn_around_time << "\t" << endl;;
        cur = cur->next;
    }
}

void display_stat(struct PROCESS *processes){
    long total_waiting_time=0,total_turn_around_time=0,i=0;
    struct PROCESS *cur=processes;
    while(cur!=NULL){
        i++;
        total_waiting_time += cur->waiting_time;
        total_turn_around_time += cur->turn_around_time;
        cur = cur->next;
    }
    if(i!=0){
        cout << "Average Waiting Time : " << total_waiting_time/i << endl;
        cout << "Average Turn Around Time : " << total_turn_around_time/i << endl;
    } else
        cout << "No process is there...Please generate them first" << endl;
}

void set_remaining_burst_time(struct PROCESS *processes){
    struct PROCESS *cur=processes;
    while(cur!=NULL){
        cur->remaining_burst_time=cur->burst_time;
        cur = cur->next;
    }
}

void sch_fcfs(struct PROCESS *processes){
    long _clock=0;
    struct PROCESS *cur=processes;
    if(cur!=NULL)
        _clock=cur->arrival_time;
    while(cur!=NULL){
        if(_clock<cur->arrival_time)
            _clock=cur->arrival_time;
        cur->waiting_time=_clock-cur->arrival_time;
        _clock +=cur->burst_time;
        cur->turn_around_time=_clock-cur->arrival_time;
        cur=cur->next;
    }
}

void sch_sjf(struct PROCESS *processes){
    long _clock=0;
    struct PROCESS *cur=processes,*ready=NULL;
    if(cur!=NULL)
        _clock=cur->arrival_time;
    while(cur!=NULL||ready!=NULL){
        if(cur!=NULL){
            if(_clock<cur->arrival_time)
                _clock=cur->arrival_time;
            while(cur!=NULL && cur->arrival_time<=_clock){
                insert_process_burst_time(&ready,copyNode(cur));
                cur=cur->next;
            }
        }
        if(ready!=NULL){
            struct PROCESS *tmp=find_process_node(processes,ready->id);
            tmp->waiting_time=_clock-tmp->arrival_time;
            _clock +=tmp->burst_time;
            tmp->turn_around_time=_clock-tmp->arrival_time;
            delete_process(&ready);
        }
    }
}

void sch_srtf(struct PROCESS *processes) {
    long _clock=0;
    struct PROCESS *cur=processes,*ready=NULL, *p;
    set_remaining_burst_time(processes);
    while(cur!=NULL || ready!=NULL) {
        struct PROCESS *tmp;
        if(cur!=NULL){
            if(_clock<cur->arrival_time && ready==NULL)
                _clock=cur->arrival_time;
            while(cur!=NULL && cur->arrival_time<=_clock){
                insert_process_remaining_burst_time(&ready,copyNode(cur));
                cur=cur->next;
            }
        }
        if(ready!=NULL){
            tmp=ready;
            if(cur!=NULL && cur->arrival_time-_clock<tmp->remaining_burst_time) {
                if(tmp->last_quantum==0)
                    tmp->waiting_time=_clock-tmp->arrival_time;
                else
                    tmp->waiting_time+=_clock-tmp->last_quantum;
                tmp->remaining_burst_time-=cur->arrival_time-_clock;
                _clock+=cur->arrival_time-_clock;
                tmp->last_quantum=_clock;
                insert_process_remaining_burst_time(&ready,copyNode(tmp));
            } else {
                if(tmp->last_quantum==0)
                    tmp->waiting_time=_clock-tmp->arrival_time;
                else
                    tmp->waiting_time+=_clock-tmp->last_quantum;
                p=find_process_node(processes, tmp->id);
                p->waiting_time = tmp->waiting_time;
                _clock+=tmp->remaining_burst_time;
                p->turn_around_time=_clock-p->arrival_time;
            }
            delete_process(&ready);
        }
    }
}

void sch_rr(struct PROCESS *processes, int quantum){
    long _clock=0;
    struct PROCESS *cur=processes,*ready=NULL,*waiting=NULL,*p;
    set_remaining_burst_time(processes);
    while(cur!=NULL || ready!=NULL || waiting!=NULL){
        struct PROCESS *tmp;
        if(cur!=NULL){
            if(_clock<cur->arrival_time && ready==NULL && waiting==NULL)
                _clock=cur->arrival_time;
            while(cur!=NULL && cur->arrival_time<=_clock){
                insert_process_end(&ready,copyNode(cur));
                cur=cur->next;
            }
        }
        while(waiting!=NULL){
            insert_process_end(&ready,copyNode(waiting));
            delete_process(&waiting);
        }

        if(ready!=NULL){
            tmp=ready;
            if(tmp->remaining_burst_time>quantum){
                if(tmp->last_quantum==0)
                    tmp->waiting_time=_clock-tmp->arrival_time;
                else
                    tmp->waiting_time+=_clock-tmp->last_quantum;
                _clock+=quantum;
                tmp->remaining_burst_time-=quantum;
                tmp->last_quantum=_clock;
                insert_process_end(&waiting,copyNode(tmp));
            } else {
                p=find_process_node(processes, tmp->id);
                if(tmp->last_quantum==0)
                    tmp->waiting_time=_clock-tmp->arrival_time;
                else
                    tmp->waiting_time+=_clock-tmp->last_quantum;
                p->waiting_time=tmp->waiting_time;
                _clock+=tmp->remaining_burst_time;
                p->turn_around_time=_clock-p->arrival_time;
            }
            delete_process(&ready);
        }
    }
}

int main(){
    int ch, q;
    struct PROCESS *processes=NULL;
    cout << "\tScheduling" << endl;
    do{
        cout << "1. Generate Process" << endl;
        cout << "2. Display Process" << endl;
        cout << "3. Display Process  [PID]" << endl;
        cout << "4. Display Process  [AT]" << endl;
        cout << "5. Display Process  [BT]" << endl;
        cout << "6. FCFS" << endl;
        cout << "7. SJF" << endl;
        cout << "8. SRTF" << endl;
        cout << "9. RR" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter choice : ";
        cin >> ch;
        switch (ch){
        case 1:
            generate_process(&processes);
            break;
        case 2:
            display_process(processes);
            break;
        case 3:
            sortBy_pid(&processes);
            display_process(processes);
            break;
        case 4:
            sortBy_arrival_time(&processes);
            display_process(processes);
            break;
        case 5:
            sortBy_burst_time(&processes);
            display_process(processes);
            break;
        case 6:
            sortBy_arrival_time(&processes);
            sch_fcfs(processes);
            display_process(processes);
            display_stat(processes);
            break;
        case 7:
            sortBy_arrival_time(&processes);
            sch_sjf(processes);
            display_process(processes);
            display_stat(processes);
            break;
        case 8:
            sortBy_arrival_time(&processes);
            sch_srtf(processes);
            display_process(processes);
            display_stat(processes);
            break;
        case 9:
            sortBy_arrival_time(&processes);
            cout << "Enter size of quantum  [Minimum : 5] : ";
            cin >> q;
            if(q<5)
                q=5;
            sch_rr(processes,q);
            display_process(processes);
            display_stat(processes);
            break;
        }
    } while(ch!=0);

}
