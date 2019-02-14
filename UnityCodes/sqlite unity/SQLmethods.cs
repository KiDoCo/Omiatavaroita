using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

//List of events
public enum EVENT { PlaySFX, PlayMusic, StopSound, AINodeSpawn, Increase, RoundBegin, RoundEnd, FoodSpawn };

//list of sounds
public enum SFXEvent { Eat, Hurt, Lose, RoundEnd, RoundBegin, Victory }; // ADD death when clip available

public enum MusicEvent { Ambient, Hunting, MainMenu };

public static class EventManager
{
    private static Dictionary<EVENT, Action> actionEventTable = new Dictionary<EVENT, Action>();
    //object is instance
    private static Dictionary<EVENT, Action<object>> GeneralDic = new Dictionary<EVENT, Action<object>>();

    /// <summary>
    /// Adds a new action or adds new method to existing entry to dictionary and stores it to event list 
    /// </summary>
    /// <param name="evnt"></param>
    /// <param name="action"></param>
    public static void ActionAddHandler(EVENT evnt, Action action)
    {
        if (!actionEventTable.ContainsKey(evnt))
        {
            actionEventTable[evnt] = action;
        }
        else
        {
            actionEventTable[evnt] += action;
        }
    }

    public static void ActionDeleteHandler(EVENT evnt)
    {
        if (actionEventTable.ContainsKey(evnt))
        {
            actionEventTable.Remove(evnt);
        }
    }

    /// <summary>
    /// Adds a new sound action or adds a new method to existing entry to dictionary
    /// </summary>
    /// <param name="evnt"></param>
    /// <param name="action"></param>
    public static void SoundAddHandler(EVENT evnt, Action<object> action)
    {
        if (!GeneralDic.ContainsKey(evnt))
        {
            GeneralDic[evnt] = action;
        }
        else
        {
            GeneralDic[evnt] += action;
        }
    }

    /// <summary>
    /// Calls a action event specified in the parameter
    /// </summary>
    /// <param name="evnt"></param>
    public static void Broadcast(EVENT evnt)
    {
        actionEventTable[evnt]?.Invoke();
    }

    /// <summary>
    /// Calls a sound action event specified in the parameter
    /// </summary>
    /// <param name="evnt"></param>
    /// <param name="source"></param>
    public static void SoundBroadcast(EVENT evnt, object source)
    {
        GeneralDic[evnt]?.Invoke(source);
    }

    //List of events and methods in that event

    /* SoundEffects
     Sounds are played through sfxmethod and musicmethod. 
     fomod?
     Clip is determined on delegate call
     */

    /*Actionhandler
     Event increase = Coral : increasefood()
     Event UpdateExperience = UImanager : UpdateExperience
     Event RoundEnd = gamemanager : EndMatch
     */
}
