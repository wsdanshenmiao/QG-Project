﻿using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;

public class WavesCascade
{
    public RenderTexture Displacement => displacement;
    public RenderTexture Derivatives => derivatives;
    public RenderTexture Turbulence => turbulence;

    public Texture2D GaussianNoise => gaussianNoise;
    public RenderTexture PrecomputedData => precomputedData;
    public RenderTexture InitialSpectrum => initialSpectrum;

    public float lambda;

    readonly int size;
    readonly ComputeShader initialSpectrumShader;
    readonly ComputeShader timeDependentSpectrumShader;
    readonly ComputeShader texturesMergerShader;
    readonly FFT fft;
    readonly Texture2D gaussianNoise;
    readonly ComputeBuffer paramsBuffer;
    readonly RenderTexture initialSpectrum;
    readonly RenderTexture precomputedData;
    
    readonly RenderTexture buffer;
    readonly RenderTexture DxDz;
    readonly RenderTexture DyDxz;
    readonly RenderTexture DyxDyz;
    readonly RenderTexture DxxDzz;

    readonly RenderTexture displacement;
    readonly RenderTexture derivatives;
    readonly RenderTexture turbulence;

    

    public WavesCascade(int size,
                        ComputeShader initialSpectrumShader,
                        ComputeShader timeDependentSpectrumShader,
                        ComputeShader texturesMergerShader,
                        FFT fft,
                        Texture2D gaussianNoise)
    {
        this.size = size;
        this.initialSpectrumShader = initialSpectrumShader;
        this.timeDependentSpectrumShader = timeDependentSpectrumShader;
        this.texturesMergerShader = texturesMergerShader;
        this.fft = fft;
        this.gaussianNoise = gaussianNoise;

        KERNEL_INITIAL_SPECTRUM = initialSpectrumShader.FindKernel("CalculateInitialSpectrum");
        KERNEL_CONJUGATE_SPECTRUM = initialSpectrumShader.FindKernel("CalculateConjugatedSpectrum");
        KERNEL_TIME_DEPENDENT_SPECTRUMS = timeDependentSpectrumShader.FindKernel("CalculateAmplitudes");
        KERNEL_RESULT_TEXTURES = texturesMergerShader.FindKernel("FillResultTextures");

        initialSpectrum = FFT.CreateRenderTexture(size, RenderTextureFormat.ARGBFloat);
        precomputedData = FFT.CreateRenderTexture(size, RenderTextureFormat.ARGBFloat);
        displacement = FFT.CreateRenderTexture(size, RenderTextureFormat.ARGBFloat);
        derivatives = FFT.CreateRenderTexture(size, RenderTextureFormat.ARGBFloat, true);
        turbulence = FFT.CreateRenderTexture(size, RenderTextureFormat.ARGBFloat, true);
        paramsBuffer = new ComputeBuffer(2, 8 * sizeof(float));

        buffer = FFT.CreateRenderTexture(size);
        DxDz = FFT.CreateRenderTexture(size);
        DyDxz = FFT.CreateRenderTexture(size);
        DyxDyz = FFT.CreateRenderTexture(size);
        DxxDzz = FFT.CreateRenderTexture(size);
    }

    public void Dispose()
    {
        paramsBuffer?.Release();
    }

    public void CalculateInitials(WavesSettings wavesSettings, float lengthScale,
                                  float cutoffLow, float cutoffHigh)
    {
        lambda = wavesSettings.lambda;

        initialSpectrumShader.SetInt(SIZE_PROP, size);
        initialSpectrumShader.SetFloat(LENGTH_SCALE_PROP, lengthScale);
        initialSpectrumShader.SetFloat(CUTOFF_HIGH_PROP, cutoffHigh);
        initialSpectrumShader.SetFloat(CUTOFF_LOW_PROP, cutoffLow);
        wavesSettings.SetParametersToShader(initialSpectrumShader, KERNEL_INITIAL_SPECTRUM, paramsBuffer);

        initialSpectrumShader.SetTexture(KERNEL_INITIAL_SPECTRUM, H0K_PROP, buffer);
        initialSpectrumShader.SetTexture(KERNEL_INITIAL_SPECTRUM, PRECOMPUTED_DATA_PROP, precomputedData);
        initialSpectrumShader.SetTexture(KERNEL_INITIAL_SPECTRUM, NOISE_PROP, gaussianNoise);
        initialSpectrumShader.Dispatch(KERNEL_INITIAL_SPECTRUM, size / X, size / Y, 1);

        initialSpectrumShader.SetTexture(KERNEL_CONJUGATE_SPECTRUM, H0_PROP, initialSpectrum);
        initialSpectrumShader.SetTexture(KERNEL_CONJUGATE_SPECTRUM, H0K_PROP, buffer);
        initialSpectrumShader.Dispatch(KERNEL_CONJUGATE_SPECTRUM, size / X, size / Y, 1);
    }

    public void CalculateWavesAtTime(float time)
    {
        // 计算复振幅
        timeDependentSpectrumShader.SetTexture(KERNEL_TIME_DEPENDENT_SPECTRUMS, Dx_Dz_PROP, DxDz);
        timeDependentSpectrumShader.SetTexture(KERNEL_TIME_DEPENDENT_SPECTRUMS, Dy_Dxz_PROP, DyDxz);
        timeDependentSpectrumShader.SetTexture(KERNEL_TIME_DEPENDENT_SPECTRUMS, Dyx_Dyz_PROP, DyxDyz);
        timeDependentSpectrumShader.SetTexture(KERNEL_TIME_DEPENDENT_SPECTRUMS, Dxx_Dzz_PROP, DxxDzz);
        timeDependentSpectrumShader.SetTexture(KERNEL_TIME_DEPENDENT_SPECTRUMS, H0_PROP, initialSpectrum);
        timeDependentSpectrumShader.SetTexture(KERNEL_TIME_DEPENDENT_SPECTRUMS, PRECOMPUTED_DATA_PROP, precomputedData);
        timeDependentSpectrumShader.SetFloat(TIME_PROP, time);
        timeDependentSpectrumShader.Dispatch(KERNEL_TIME_DEPENDENT_SPECTRUMS, size / X, size / Y, 1);

        // 利用傅里叶逆变换计算复振幅
        fft.IFFT2D(DxDz, buffer, true, false, true);
        fft.IFFT2D(DyDxz, buffer, true, false, true);
        fft.IFFT2D(DyxDyz, buffer, true, false, true);
        fft.IFFT2D(DxxDzz, buffer, true, false, true);

        // 填充偏移和法线贴图
        texturesMergerShader.SetFloat("DeltaTime", Time.deltaTime);

        texturesMergerShader.SetTexture(KERNEL_RESULT_TEXTURES, Dx_Dz_PROP, DxDz);
        texturesMergerShader.SetTexture(KERNEL_RESULT_TEXTURES, Dy_Dxz_PROP, DyDxz);
        texturesMergerShader.SetTexture(KERNEL_RESULT_TEXTURES, Dyx_Dyz_PROP, DyxDyz);
        texturesMergerShader.SetTexture(KERNEL_RESULT_TEXTURES, Dxx_Dzz_PROP, DxxDzz);
        texturesMergerShader.SetTexture(KERNEL_RESULT_TEXTURES, DISPLACEMENT_PROP, displacement);
        texturesMergerShader.SetTexture(KERNEL_RESULT_TEXTURES, DERIVATIVES_PROP, derivatives);
        texturesMergerShader.SetTexture(KERNEL_RESULT_TEXTURES, TURBULENCE_PROP, turbulence);
        texturesMergerShader.SetFloat(LAMBDA_PROP, lambda);
        texturesMergerShader.Dispatch(KERNEL_RESULT_TEXTURES, size / X, size / Y, 1);

        derivatives.GenerateMips();
        turbulence.GenerateMips();
    }

    const int X = 8;
    const int Y = 8;

    // 各种Kernel
    int KERNEL_INITIAL_SPECTRUM;
    int KERNEL_CONJUGATE_SPECTRUM;
    int KERNEL_TIME_DEPENDENT_SPECTRUMS;
    int KERNEL_RESULT_TEXTURES;

    // 各种变量
    readonly int SIZE_PROP = Shader.PropertyToID("Size");
    readonly int LENGTH_SCALE_PROP = Shader.PropertyToID("LengthScale");
    readonly int CUTOFF_HIGH_PROP = Shader.PropertyToID("CutoffHigh");
    readonly int CUTOFF_LOW_PROP = Shader.PropertyToID("CutoffLow");

    readonly int NOISE_PROP = Shader.PropertyToID("Noise");
    readonly int H0_PROP = Shader.PropertyToID("H0");
    readonly int H0K_PROP = Shader.PropertyToID("H0K");
    readonly int PRECOMPUTED_DATA_PROP = Shader.PropertyToID("WavesData");
    readonly int TIME_PROP = Shader.PropertyToID("Time");

    readonly int Dx_Dz_PROP = Shader.PropertyToID("Dx_Dz");
    readonly int Dy_Dxz_PROP = Shader.PropertyToID("Dy_Dxz");
    readonly int Dyx_Dyz_PROP = Shader.PropertyToID("Dyx_Dyz");
    readonly int Dxx_Dzz_PROP = Shader.PropertyToID("Dxx_Dzz");
    readonly int LAMBDA_PROP = Shader.PropertyToID("Lambda");

    readonly int DISPLACEMENT_PROP = Shader.PropertyToID("Displacement");
    readonly int DERIVATIVES_PROP = Shader.PropertyToID("Derivatives");
    readonly int TURBULENCE_PROP = Shader.PropertyToID("Turbulence"); 
}
