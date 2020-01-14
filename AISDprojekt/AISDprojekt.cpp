#include <iostream>



struct Node {
	int data;
	struct Node* next;
	struct Node* prev;
};


struct Node* GetNewNode(int x) {
	struct Node* newNode = new Node;
	newNode->data = x;
	newNode->prev = NULL;
	newNode->next = NULL;
	return newNode;
}



void InsertAtEnd(int x, struct Node **root) {
	struct Node* temp = *root;
	struct Node* newNode = GetNewNode(x);
	if (*root == NULL) {
		*root = newNode;
		return;
	}
	while (temp->next != NULL) temp = temp->next; 
	temp->next = newNode;
	newNode->prev = temp;
}
void InsertAtObrotnica(struct Node **obrotnica, struct Node **tor,int ile) {
	
	struct Node* temp = *obrotnica;
	if (*tor == NULL) return;
	if (ile == 0) return;
	if (*obrotnica == NULL)
	{
		if (*tor == NULL) return;
		*obrotnica = *tor;
		temp = *obrotnica;
		int i = 1;
		if (ile > 10)ile = 10;
		while (temp->next != NULL && i < ile)
		{
			temp = temp->next;
			i++;
		}
		*tor = temp->next;
		if (*tor != NULL)
		{
			(*tor)->prev = NULL;
		}
		temp->next = NULL;
		return;
	}
	int licznik = 1;
	int j = 0;
	while (temp->next != NULL)
	{
		temp = temp->next;
		licznik++;
	}
	temp->next = *tor;
	(*tor)->prev = temp;
	while (temp->next != NULL && licznik < 10 && j<ile)
	{
		temp = temp->next;
		j++;
		licznik++;
	}
	*tor = temp->next;
	if (*tor != NULL) (*tor)->prev = NULL;
	temp->next = NULL;
}
void InsertAtTrack(struct Node **obrotnica, struct Node **tor, int ile) {
	struct Node* temp = *obrotnica;
	if (*obrotnica == NULL) return;
	if (ile == 0) return;
	if (*tor == NULL)
	{
		int obecnie = 1;
		while (temp->next != NULL)
		{
			temp = temp->next;
			obecnie++;
		}
		if (ile > obecnie) ile = obecnie;
		for (int i = 1; i < ile; i++)
		{
			temp = temp->prev;
		}
		*tor = temp;
		if (temp->prev != NULL) {
			temp = temp->prev;
			temp->next = NULL;
			if (*tor != NULL)(*tor)->prev = NULL;
		}
		else *obrotnica = NULL;

		return;
	}
	int k = 1;
	while (temp->next != NULL)
	{
		temp = temp->next;
		k++;
	}
	if (ile > k ) ile = k;
	temp->next = *tor;
	(*tor)->prev = temp;

	for (int i = 1; i < ile; i++)
	{
		temp = temp->prev;
	}

	*tor = temp;
	if (temp->prev != NULL) {
		temp = temp->prev;
		temp->next = NULL;
		if (*tor != NULL)(*tor)->prev = NULL;
	}
	else *obrotnica = NULL;
}

void Print(struct Node* root) {
	struct Node* temp = root;
	
	if (temp == NULL)
	{
		printf("0\n"); 
		return;
	}
	int licznik = 0;
	if (root != NULL)licznik = 1;
	while (temp->next != NULL)
	{
		temp = temp->next;
		licznik++;
	}
	printf("%d ", licznik);
	while (root != NULL) {
		printf("%d ", root->data);
		root = root->next;
	}
	printf("\n");
}

void ReversePrint(struct Node* root) {
	struct Node* temp = root;

	if (temp == NULL)
	{
		printf("0\n");
		return;
	}
	int licznik = 0;
	if (root != NULL)licznik = 1;
	while (temp->next != NULL) {
		temp = temp->next;
		licznik++;
	}
	
	printf("%d ", licznik);
	while (temp != NULL) {
		printf("%d ", temp->data);
		temp = temp->prev;
	}
	printf("\n");
}


int main()
{
	int TrackCount = 0;
	int TrainCount = 0;
	int ActionCount = 0;
	int zwrotnica_tor = 1;
	int temp = 0;
	char Action = '\0';
	std::cin >> TrackCount;
	TrackCount += 1;
	
	struct Node** root=new Node*[TrackCount];  
	for (int i = 0; i < TrackCount; i++)
	{
		root[i] = NULL;
	}
	
	for (int j = 1; j < TrackCount; j++)
	{
		TrainCount = 0;
		std::cin >> TrainCount;
		for (int k = 0; k < TrainCount; k++)
		{
			long long temp = 0;
			std::cin >> temp;
			InsertAtEnd(temp, &root[j]);
		}
	}
	std::cin >> ActionCount;
	for (int i = 0; i < ActionCount; i++)
	{
		std::cin >>(char) Action >>(int) temp;


		switch (Action)
		{
		case 'w':
			InsertAtObrotnica(&root[0], &root[zwrotnica_tor],temp);
			break;
		case 'z': 
			if (zwrotnica_tor == TrackCount-1) zwrotnica_tor = 0;
			zwrotnica_tor = (zwrotnica_tor + temp) % (TrackCount - 1);
			if(zwrotnica_tor ==0) zwrotnica_tor=TrackCount-1;
			break;
		case 'j':
			InsertAtTrack(&root[0], &root[zwrotnica_tor],temp);
			break;
		case 'o': 
			if (zwrotnica_tor == TrackCount-1) zwrotnica_tor = 0;
			zwrotnica_tor = (zwrotnica_tor - temp) % (TrackCount-1);
			
			if (zwrotnica_tor < 0) {
				zwrotnica_tor = -zwrotnica_tor;
				zwrotnica_tor = TrackCount - 1 - zwrotnica_tor;
			}
			if (zwrotnica_tor == 0) zwrotnica_tor = TrackCount - 1;
			break;
		}
	}
	ReversePrint(root[0]);
	int reszta = TrackCount-1;
	for (int i = zwrotnica_tor; i < TrackCount; i++)
	{
		Print(root[i]);
		reszta--;
	}
	for (int i = 1; i <= reszta; i++)
	{
		Print(root[i]);
	}
    return 0;
}

