﻿#include "Utility/AlsGameplayTags.h"

namespace AlsViewModeTags
{
	UE_DEFINE_GAMEPLAY_TAG(FirstPerson, FName{TEXTVIEW("Als.ViewMode.FirstPerson")})
	UE_DEFINE_GAMEPLAY_TAG(ThirdPerson, FName{TEXTVIEW("Als.ViewMode.ThirdPerson")})
}

namespace AlsLocomotionModeTags
{
	UE_DEFINE_GAMEPLAY_TAG(Grounded,	FName{TEXTVIEW("Als.LocomotionMode.Grounded")})
	UE_DEFINE_GAMEPLAY_TAG(InAir,		FName{TEXTVIEW("Als.LocomotionMode.InAir")})
	UE_DEFINE_GAMEPLAY_TAG(InWater,		FName{TEXTVIEW("Als.LocomotionMode.InWater")})
	UE_DEFINE_GAMEPLAY_TAG(Gliding,		FName{TEXTVIEW("Als.LocomotionMode.Gliding")})
}

namespace AlsRotationModeTags
{
	UE_DEFINE_GAMEPLAY_TAG(VelocityDirection, FName{TEXTVIEW("Als.RotationMode.VelocityDirection")})
	UE_DEFINE_GAMEPLAY_TAG(ViewDirection, FName{TEXTVIEW("Als.RotationMode.ViewDirection")})
	UE_DEFINE_GAMEPLAY_TAG(Aiming, FName{TEXTVIEW("Als.RotationMode.Aiming")})
	UE_DEFINE_GAMEPLAY_TAG(Targeting, FName{TEXTVIEW("Als.RotationMode.Targeting")})
}

namespace AlsStanceTags
{
	UE_DEFINE_GAMEPLAY_TAG(Standing, FName{TEXTVIEW("Als.Stance.Standing")})
	UE_DEFINE_GAMEPLAY_TAG(Crouching, FName{TEXTVIEW("Als.Stance.Crouching")})
}

namespace AlsGaitTags
{
	UE_DEFINE_GAMEPLAY_TAG(Walking, FName{TEXTVIEW("Als.Gait.Walking")})
	UE_DEFINE_GAMEPLAY_TAG(Running, FName{TEXTVIEW("Als.Gait.Running")})
	UE_DEFINE_GAMEPLAY_TAG(Sprinting, FName{TEXTVIEW("Als.Gait.Sprinting")})
}

namespace AlsOverlayModeTags
{
	UE_DEFINE_GAMEPLAY_TAG(Default, FName{TEXTVIEW("Als.OverlayMode.Default")})
	UE_DEFINE_GAMEPLAY_TAG(Masculine, FName{TEXTVIEW("Als.OverlayMode.Masculine")})
	UE_DEFINE_GAMEPLAY_TAG(Feminine, FName{TEXTVIEW("Als.OverlayMode.Feminine")})
	UE_DEFINE_GAMEPLAY_TAG(Injured, FName{TEXTVIEW("Als.OverlayMode.Injured")})
	UE_DEFINE_GAMEPLAY_TAG(HandsTied, FName{TEXTVIEW("Als.OverlayMode.HandsTied")})
	UE_DEFINE_GAMEPLAY_TAG(Rifle, FName{TEXTVIEW("Als.OverlayMode.Rifle")})
	UE_DEFINE_GAMEPLAY_TAG(PistolOneHanded, FName{TEXTVIEW("Als.OverlayMode.PistolOneHanded")})
	UE_DEFINE_GAMEPLAY_TAG(PistolTwoHanded, FName{TEXTVIEW("Als.OverlayMode.PistolTwoHanded")})
	UE_DEFINE_GAMEPLAY_TAG(Bow, FName{TEXTVIEW("Als.OverlayMode.Bow")})
	UE_DEFINE_GAMEPLAY_TAG(Torch, FName{TEXTVIEW("Als.OverlayMode.Torch")})
	UE_DEFINE_GAMEPLAY_TAG(Binoculars, FName{TEXTVIEW("Als.OverlayMode.Binoculars")})
	UE_DEFINE_GAMEPLAY_TAG(Box, FName{TEXTVIEW("Als.OverlayMode.Box")})
	UE_DEFINE_GAMEPLAY_TAG(Barrel, FName{TEXTVIEW("Als.OverlayMode.Barrel")})
	UE_DEFINE_GAMEPLAY_TAG(Sword, FName{TEXTVIEW("Als.OverlayMode.Sword")})
	UE_DEFINE_GAMEPLAY_TAG(Hatchet, FName{TEXTVIEW("Als.OverlayMode.Hatchet")})
	UE_DEFINE_GAMEPLAY_TAG(PickAxe, FName{TEXTVIEW("Als.OverlayMode.PickAxe")})
	UE_DEFINE_GAMEPLAY_TAG(Hammer, FName{TEXTVIEW("Als.OverlayMode.Hammer")})
	UE_DEFINE_GAMEPLAY_TAG(Spear, FName{TEXTVIEW("Als.OverlayMode.Spear")})
	UE_DEFINE_GAMEPLAY_TAG(Dagger, FName{TEXTVIEW("Als.OverlayMode.Dagger")})
	UE_DEFINE_GAMEPLAY_TAG(SwordTwoHanded, FName{TEXTVIEW("Als.OverlayMode.SwordTwoHanded")})
	UE_DEFINE_GAMEPLAY_TAG(Throw, FName{TEXTVIEW("Als.OverlayMode.Throw")})
}

namespace AlsLocomotionActionTags
{
	UE_DEFINE_GAMEPLAY_TAG(Mantling, FName{TEXTVIEW("Als.LocomotionAction.Mantling")})
	UE_DEFINE_GAMEPLAY_TAG(Ragdolling, FName{TEXTVIEW("Als.LocomotionAction.Ragdolling")})
	UE_DEFINE_GAMEPLAY_TAG(GettingUp, FName{TEXTVIEW("Als.LocomotionAction.GettingUp")})
	UE_DEFINE_GAMEPLAY_TAG(Rolling, FName{TEXTVIEW("Als.LocomotionAction.Rolling")})
}

namespace AlsGroundedEntryModeTags
{
	UE_DEFINE_GAMEPLAY_TAG(FromRoll, FName{TEXTVIEW("Als.GroundedEntryMode.FromRoll")})
}

namespace AlsInputActionTags
{
	UE_DEFINE_GAMEPLAY_TAG(LockJumping, FName{TEXTVIEW("Character.State.LockJumping")})
	UE_DEFINE_GAMEPLAY_TAG(LockRolling, FName{TEXTVIEW("Character.State.LockRolling")})
	UE_DEFINE_GAMEPLAY_TAG(OverlayAction, FName{TEXTVIEW("Character.State.OverlayAction")})
	UE_DEFINE_GAMEPLAY_TAG(LockMoveInput, FName{TEXTVIEW("Character.State.LockMoveInput")})
}

namespace AlsCharacterStateTags
{
	UE_DEFINE_GAMEPLAY_TAG(Attack, FName{TEXTVIEW("Character.State.Attack")})
	UE_DEFINE_GAMEPLAY_TAG(WeakAttack, FName{TEXTVIEW("Character.State.Attack.Weak")})
	UE_DEFINE_GAMEPLAY_TAG(HeavyAttack, FName{TEXTVIEW("Character.State.Attack.Heavy")})
	UE_DEFINE_GAMEPLAY_TAG(ComboAttack, FName{TEXTVIEW("Character.State.ComboAttack")})
	UE_DEFINE_GAMEPLAY_TAG(Blocking, FName{TEXTVIEW("Character.State.Blocking")})
	UE_DEFINE_GAMEPLAY_TAG(Parrying, FName{TEXTVIEW("Character.State.Parrying")})
	UE_DEFINE_GAMEPLAY_TAG(Invincibility, FName{TEXTVIEW("Character.State.Invincibility")})
	UE_DEFINE_GAMEPLAY_TAG(Hit, FName{TEXTVIEW("Character.State.Hit")})
	UE_DEFINE_GAMEPLAY_TAG(PerfectDodge, FName{TEXTVIEW("Character.State.PerfectDodge")})
}

namespace AlsCombatTags
{
	UE_DEFINE_GAMEPLAY_TAG(NextComboAttack, FName{TEXTVIEW("Combat.Combo.Next")})
}