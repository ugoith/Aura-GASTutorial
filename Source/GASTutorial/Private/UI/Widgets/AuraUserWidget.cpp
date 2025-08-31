  // Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/AuraUserWidget.h"
////在AuraHUD中的InitOverlay函数中调用
  void UAuraUserWidget::SetWidgetController(UObject* InWidgetController)
  {
  	WidgetController =InWidgetController;
  	WidgetControllerSet();
  }
