using System.Collections.Generic;
using UnityEngine.UI;
using TMPro;
using System;

public class UIManager : Singleton<UIManager>
{
    private PlayerStats m_PlayerStats;

    private Slider m_PlayerHPSlider;
    private Slider m_PlayerEXSlider;

    private TMP_Text m_HPText;
    private TMP_Text m_LVText;
    private TMP_Text m_WaveNum;
    private TMP_Text m_CountDown;

    // Start is called before the first frame update
    void Start()
    {
        m_PlayerStats = FindObjectOfType<PlayerStats>();
        InitUISlider();
        InitText();
    }

    // Update is called once per frame
    void Update()
    {
        UpdatePlayerUI();
        UpdateText();
    }

    /// <summary>
    /// 初始化UI文本
    /// </summary>
    private void InitText()
    {
        TMP_Text[] texts = GetComponentsInChildren<TMP_Text>();
        m_HPText = Array.Find<TMP_Text>(texts, data => data.name == "HPNum");
        m_LVText = Array.Find<TMP_Text>(texts, data => data.name == "LVNum");
        m_CountDown = Array.Find<TMP_Text>(texts, data => data.name == "CountDown");
        m_WaveNum = Array.Find<TMP_Text>(texts, data => data.name == "WaveNumber");
    }

    /// <summary>
    /// 初始化信息条
    /// </summary>
    private void InitUISlider()
    {
        List<Slider> sliderList = new List<Slider>();
        GetComponentsInChildren<Slider>(sliderList);
        m_PlayerHPSlider = sliderList.Find(data => { return data.name == "PlayerHP"; });
        m_PlayerEXSlider = sliderList.Find(data => { return data.name == "PlayerEX"; });

        m_PlayerHPSlider.maxValue = m_PlayerStats.MaxHP;
        m_PlayerHPSlider.value = m_PlayerStats.CurrentHP;

        m_PlayerEXSlider.maxValue = m_PlayerStats.MaxExperience;
        m_PlayerEXSlider.value = m_PlayerStats.Experience;
    }

    private void UpdateText()
    {
        m_HPText.text = m_PlayerStats.CurrentHP.ToString() + '/' + m_PlayerStats.MaxHP.ToString();
        m_LVText.text = "LV:" + m_PlayerStats.Level.ToString();
        
        m_WaveNum.text = '第' + GameManager.Instance.CurrentWaveNumber.ToString() + '波';
        int time = (int)GameManager.Instance.CurrentWaveTime;
        m_CountDown.text = time.ToString();
    }

    private void UpdatePlayerUI()
    {
        m_PlayerHPSlider.value = m_PlayerStats.CurrentHP;

        m_PlayerEXSlider.maxValue = m_PlayerStats.MaxExperience;
        m_PlayerEXSlider.value = m_PlayerStats.Experience;
    }
}
