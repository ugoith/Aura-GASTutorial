--
-- DESCRIPTION
--
-- @COMPANY **
-- @AUTHOR **
-- @DATE ${date} ${time}
--下面的这个必须是智能提示中定义的类
---@type BP_DebugFunction_C
local BP_DebugFunction_C = require("BP.FunctionLibrary.BP_DebugFunction_C")--必须带有_C后缀否则无法使用该类的函数或变量
---@type BP_AuraCharacter_C
local M = UnLua.Class()
function M:Test(BaseValue, Health, Mana)
    self.Overridden.Test(self,BaseValue,Health,Mana)
    UE.UKismetSystemLibrary.PrintString(self,"Lua: Hello",
    true,false,UE.FLinearColor(1,0,0,1),5,"")
    BP_DebugFunction_C.PrintString(self,"LuaFunctionLibrary: Hello",
            true,false,UE.FLinearColor(1,0,0,1),5,"")

end
-- function M:Initialize(Initializer)
-- end

-- function M:UserConstructionScript()
-- end

--function M:ReceiveBeginPlay()
   -- self.Overridden:ReceiveBeginPlay()
--end

-- function M:ReceiveEndPlay()
-- end

-- function M:ReceiveTick(DeltaSeconds)
-- end

-- function M:ReceiveAnyDamage(Damage, DamageType, InstigatedBy, DamageCauser)
-- end

-- function M:ReceiveActorBeginOverlap(OtherActor)
-- end

-- function M:ReceiveActorEndOverlap(OtherActor)
-- end

return M
