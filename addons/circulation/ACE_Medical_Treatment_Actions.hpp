class ACE_Medical_Treatment_Actions {
    class BasicBandage;
    class FieldDressing;
    class ApplyTourniquet;
    class RemoveTourniquet;
    class Morphine;
    class CheckPulse;
    class CPR;

    class BloodIV: BasicBandage {
    condition = QUOTE(_patient getVariable [ARR_2(QQGVAR(IVplaced), true)]) && QFUNC(removeIV);
    };

    class Painkillers: Morphine {
        displayName = CSTRING(Inject_Box_Painkillers);
        displayNameProgress = CSTRING(Using);
        allowedSelections[] = {"Head"};
        items[] = {};
        callbackSuccess = QUOTE([ARR_5('kat_Painkiller', _medic, _patient, _bodyPart, 'Painkillers')] call FUNC(removeItemfromMag));
        condition = "[_medic, 'kat_Painkiller'] call ace_common_fnc_hasMagazine || [_patient, 'kat_Painkiller'] call ace_common_fnc_hasMagazine";
        litter[] = {};
        icon = QPATHTOF(ui\icon_painkillers_action.paa);
        animationPatient = "";
        animationPatientUnconscious = "AinjPpneMstpSnonWrflDnon_rolltoback";
        animationPatientUnconsciousExcludeOn[] = {"ainjppnemstpsnonwrfldnon"};
    };
    class Carbonate: Morphine {
        displayName = CSTRING(Take_Carbonate);
        displayNameProgress = CSTRING(Using);
        category = "medication";
        treatmentLocations = 0;
        allowedSelections[] = {"Head"};
        allowSelfTreatment = 0;
        medicRequired = 1;
        treatmentTime = QGVAR(carboApp);
        items[] = {"kat_carbonate"};
        condition = QUOTE(!([_patient] call ace_common_fnc_isAwake)) && QGVAR(carbonateActive);
        patientStateCondition = 0;
        callbackSuccess = QUOTE([ARR_3(_player, _patient, 'Carbonate')] call FUNC(treatmentAdvanced_Carbonate));
        callbackFailure = "";
        callbackProgress = "";
        consumeItem = 1;
        animationPatient = "";
        animationPatientUnconscious = "";
        animationPatientUnconsciousExcludeOn[] = {""};
        animationMedic = "AinvPknlMstpSlayWrflDnon_medicOther";
        animationMedicProne = "AinvPpneMstpSlayW[wpn]Dnon_medicOther";
        animationMedicSelf = "AinvPknlMstpSlayW[wpn]Dnon_medic";
        animationMedicSelfProne = "AinvPpneMstpSlayW[wpn]Dnon_medic";
        litter[] = {};
    };
    class Naloxone: Carbonate {
        displayName = CSTRING(Take_Naloxone);
        allowedSelections[] = {"Head"};
        allowSelfTreatment = 0;
        medicRequired = 1;
        treatmentTime = QGVAR(naloApp);
        items[] = {"kat_naloxone"};
        condition = QGVAR(naloxoneActive);
        patientStateCondition = 0;
        callbackSuccess = QUOTE([ARR_3(_player, _patient, 'Naloxone')] call FUNC(treatmentAdvanced_Naloxone));
    };
    class TXA: Carbonate {
        displayName = CSTRING(Take_TXA);
        allowedSelections[] = {"LeftArm", "RightArm", "LeftLeg", "RightLeg"};
        allowSelfTreatment = 0;
        medicRequired = 1;
        treatmentTime = 5;
        items[] = {"kat_TXA"};
        condition = QUOTE(_patient getVariable [ARR_2(QQGVAR(IVplaced), true)]) && QGVAR(txaActive);
        patientStateCondition = 0;
        callbackSuccess = QUOTE([ARR_2(_player, _patient)] call FUNC(treatmentAdvanced_TXA));
    };
    class CheckBloodPressure: CheckPulse { // Remove the ability to check blood pressure at the head
        allowedSelections[] = {"LeftArm", "RightArm", "LeftLeg", "RightLeg"};
        animationPatient = "";
        animationPatientUnconscious = "AinjPpneMstpSnonWrflDnon_rolltoback";
        animationPatientUnconsciousExcludeOn[] = {"ainjppnemstpsnonwrfldnon"};
    };
    class ApplyIV: ApplyTourniquet {
        displayName = CSTRING(Apply_IV_16);
        displayNameProgress = CSTRING(Applying_IV);
        medicRequired = QUOTE(ace_medical_medicIV);
        category = "advanced";
        allowedSelections[] = {"LeftArm", "RightArm", "LeftLeg", "RightLeg"};
        items[] = {"kat_IV_16"};
        condition = QUOTE(!(_patient getVariable [ARR_2(QQGVAR(IVplaced), false)]));
        treatmentTime = QGVAR(IVestablish);
        callbackSuccess = QFUNC(applyIV);
        litter[] = {};
    };
    class RemoveIV: ApplyTourniquet {
        displayName = CSTRING(Remove_IV);
        displayNameProgress = CSTRING(Removing_IV);
        treatmentTime = 3;
        items[] = {};
        condition = QFUNC(removeIV);
        callbackSuccess = QFUNC(retrieveIV);
    };
    class Defibrillator: CPR {
        displayName = CSTRING(Defib_Action_Use);
        displayNameProgress = "$STR_ACEP_circulation_AED_PROGRESS";
        icon = QPATHTOF(ui\defib.paa);
        items[] = {"kat_AED"};
        treatmentTime = 10;
        callbackStart = "call ace_medical_treatment_fnc_cprStart; _patient setVariable ['aceP_AEDinUse', true, true];";
        callbackProgress = "call ace_medical_treatment_fnc_cprProgress; call aceP_circulation_fnc_AED_sound;";
        callbackSuccess = "[_medic, _patient, 'AED'] call aceP_circulation_fnc_AEDSuccess; _patient setVariable ['aceP_AEDinUse', false, true];";
        callbackFailure = "call ace_medical_treatment_fnc_cprFailure; _medic setVariable ['aceP_soundplayed', false, true]; _patient setVariable ['aceP_AEDinUse', false, true];";
        animationMedic = "AinvPknlMstpSnonWnonDr_medic0";
        treatmentLocations = "GVAR(useLocation_AED)";
        medicRequired = 1;
        animationPatient = "";
        animationPatientUnconscious = "AinjPpneMstpSnonWrflDnon_rolltoback";
        animationPatientUnconsciousExcludeOn[] = {"ainjppnemstpsnonwrfldnon"};
    };
    class Defibrillator_station: Defibrillator {
        displayName = CSTRING(DefibS_Action_Use);
        items[] = {};
        callbackSuccess = "[_medic, _patient, 'AED-Station'] call aceP_circulation_fnc_AEDSuccess; _patient setVariable ['aceP_AEDinUse', false, true];";
        condition = "aceP_circulation_fnc_AEDStationCondition";
        treatmentLocations = 0;
    };
    
    class Defibrillator_AED_X: Defibrillator {
        displayName = CSTRING(AED_X_Action_Use);
        displayNameProgress = CSTRING(AED_X_Action_Progress);
        items[] = {};
        callbackSuccess = "[_medic, _patient, 'AED-X'] call aceP_circulation_fnc_AEDSuccess; _patient setVariable ['aceP_AEDinUse', false, true];";
        //condition = QUOTE((_patient getVariable [ARR_2(QQGVAR(X), false)]) || [ARR_2(_medic, 'kat_AED')] call ace_common_fnc_hasItem || [ARR_2(_medic, 'kat_X_AED')] call ace_common_fnc_hasItem);
        condition = "aceP_circulation_fnc_AEDXCondition";
        medicRequired = QGVAR(medLvl_AED_X);
        icon = QPATHTOF(ui\X_Series-Device_W.paa);
    };
    
    class X_Defibrillator_AED_X: Defibrillator_AED_X {
        displayName = CSTRING(X_Action_Use);
        displayNameProgress = CSTRING(X_Action_Progress);
        items[] = {"kat_X_AED"};
        condition = QUOTE(!(_patient getVariable [ARR_2(QQGVAR(X), false)]));
        consumeItem = 1;
        medicRequired = QGVAR(medLvl_AED_X);
        callbackProgress = "";
        callbackStart = "";
        callbackFailure = "";
        callbackSuccess = QFUNC(treatmentAdvanced_X);
        icon = QPATHTOF(ui\X_Series-Device_W.paa);
    };

    class Remove_X_Defibrillator: Defibrillator_AED_X {
        displayName = CSTRING(X_Action_Remove);
        displayNameProgress = CSTRING(X_Remove_Action_Progress);
        items[] = {};
        condition = QUOTE(_patient getVariable [ARR_2(QQGVAR(X), true)]);
        treatmentTime = 5;
        medicRequired = 0;
        callbackProgress = "";
        callbackStart = "";
        callbackFailure = "";
        callbackSuccess = QUOTE([ARR_2(_medic, _patient)] call FUNC(returnAED_X));
        icon = QPATHTOF(ui\X_Series-Device_W.paa);
    };
};
