#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Contact
{
  char name[20];
  int phone;
  struct Contact *next;
};

struct Queue
{
  struct Contact *head;
  struct Contact *tail;
};
typedef struct Queue queueList;

void start(queueList *queue)
{
  queue->head = NULL;
  queue->tail = NULL;
}

int IsEmpty(queueList *queue)
{
  if (queue->head == NULL)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

void addToList(queueList *queue, char name[], int phone)
{
  struct Contact *newContact = malloc(sizeof(struct Contact));
  strcpy(newContact->name, name);
  newContact->phone = phone;
  newContact->next = NULL;

  if (IsEmpty(queue))
  {
    queue->head = newContact;
    queue->tail = newContact;
  }
  else
  {
    queue->tail->next = newContact;
    queue->tail = newContact;
  }
}

void deleteItem(queueList *queue)
{
  if (IsEmpty(queue))
  {
    printf("A fila está vazia!!!");
    return;
  }

  struct Contact *temp = queue->head;
  queue->head = queue->head->next;
  free(temp);
}

void listAgenda(queueList *queue)
{
  struct Contact *current = queue->head;

  while (current != NULL)
  {
    printf("|Nome: %s| Telefone: %d|\n", current->name, current->phone);
    current = current->next;
  }
}

void clearAgenda(queueList *queue)
{
  struct Contact *current = queue->head;
  struct Contact *temp;

  while (current != NULL)
  {
    temp = current;
    current = current->next;
    free(temp);
  }

  queue->head = NULL;
  queue->tail = NULL;
}

struct Contact *searchContact(queueList *queue, char name[])
{
  struct Contact *current = queue->head;

  while (current != NULL)
  {
    if (strcmp(current->name, name) == 0)
    {
      return current;
    }
    current = current->next;
  }
  return NULL;
}

void updateContact(queueList *queue, char name[])
{
  struct Contact *contactToUpdate = searchContact(queue, name);
  if (contactToUpdate == NULL)
  {
    printf("O contato nao existe!!\n");
    return;
  }

  printf("Digite o novo nome: ");
  scanf("%s", contactToUpdate->name);
  printf("Digite o novo telefone: ");
  scanf("%d", &(contactToUpdate->phone));

  printf("Contato atualizado com sucesso!\n");
}

int countContacts(queueList *queue)
{
  int count = 0;

  struct Contact *current = queue->head;

  while (current != NULL)
  {
    count++;

    current = current->next;
  }

  return count;
}

int main()
{
  queueList agenda;
  start(&agenda);

  int opcao;
  char name[20];
  char phoneStr[20];
  int phone;

  do
  {
    printf("Escolha uma das opcoes: \n");
    printf("[1] - Adicionar contato na agenda\n");
    printf("[2] - Mostrar contatos na agenda\n");
    printf("[3] - Atualizar contatos na agenda\n");
    printf("[4] - Verificar numero de contatos na agenda\n");
    printf("[5] - Deletar contato da agenda\n");
    printf("[6] - Sair da agenda\n");
    scanf("%d", &opcao);

    switch (opcao)
    {
    case 1:
      printf("Digite o nome: ");
      scanf("%s", name);
      printf("Digite o telefone: ");
      getchar(); // Limpa o buffer do teclado
      fgets(phoneStr, sizeof(phoneStr), stdin);
      sscanf(phoneStr, "%d", &phone);
      addToList(&agenda, name, phone);
      break;
    case 2:
      listAgenda(&agenda);
      break;
    case 3:
      printf("Digite o nome do contato que deseja atualizar: ");
      scanf("%s", name);
      updateContact(&agenda, name);
      break;
    case 4:
      printf("Total de contatos na agenda: %d\n", countContacts(&agenda));
      break;
    case 5:
      printf("Digite o nome do contato a ser deletado: ");
      scanf("%s", name);
      deleteItem(&agenda);
      break;
    case 6:
      printf("Saindo do programa!!!\n");
      break;
    default:
      printf("Opcao invalida!! Tente novamente.\n");
      break;
    }
  } while (opcao != 6);

  return 0;
}
