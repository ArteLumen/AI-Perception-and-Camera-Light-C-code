#include "MyCharacter.h"
#include "GameFramework/SpringArmComponent.h"

AMyCharacter::AMyCharacter()
{

  CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
}

void AMyCharacter::CustomFunction()
{

}
