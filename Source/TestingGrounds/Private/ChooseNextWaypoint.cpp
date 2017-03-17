// Fill out your copyright notice in the Description page of Project Settings.

#include "TestingGrounds.h"
#include "ChooseNextWaypoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "PatrolComponent.h"

EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto BlackboardComponent = OwnerComp.GetBlackboardComponent();
	
	auto CurrentIndex = BlackboardComponent->GetValueAsInt(Index.SelectedKeyName);
	
	auto AIController = OwnerComp.GetAIOwner();
	if (!ensure(AIController)) {
		EBTNodeResult::Failed;
	}
	auto Pawn = AIController->GetPawn();
	if (!ensure(Pawn)) {
		return EBTNodeResult::Failed;
	}

	UPatrolComponent *PatrolComponent = Pawn->FindComponentByClass<UPatrolComponent>();
	if (PatrolComponent) {
		auto Waypoints = PatrolComponent->GetPatrolPoints();
		auto NextWayPoint = (CurrentIndex + 1) % Waypoints.Num();
		BlackboardComponent->SetValueAsInt(Index.SelectedKeyName, NextWayPoint);
		BlackboardComponent->SetValueAsObject(Waypoint.SelectedKeyName, Waypoints[NextWayPoint]);
	}


	return EBTNodeResult::Succeeded;
}
