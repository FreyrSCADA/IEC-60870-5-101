/*****************************************************************************/
/*! \file        iec101api.cs
 *  \brief       iec101 protocol API c# wrapper file
 *  \author      FreyrSCADA Embedded Solution Pvt Ltd
 *  \copyright (c) FreyrSCADA Embedded Solution Pvt Ltd. All rights reserved.
 *
 * THIS IS PROPRIETARY SOFTWARE AND YOU NEED A LICENSE TO USE OR REDISTRIBUTE.
 *
 * THIS SOFTWARE IS PROVIDED BY FREYRSCADA AND CONTRIBUTORS ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL FREYRSCADA OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/


/*****************************************************************************/
/*! \brief iec101 types c# class  */

using System.Runtime.InteropServices;

public partial class iec101api
{

    /*! \brief          IEC101 Version Number */
    public const string IEC101_VERSION = "21.06.022";





#if Windows
        [DllImport("iec101x64d.dll", EntryPoint = "IEC101GetLibraryVersion", CallingConvention = System.Runtime.InteropServices.CallingConvention.StdCall)]
#elif Linux
     [DllImport("libx86_64-iec101.so")]
#endif
    public static extern System.IntPtr IEC101GetLibraryVersion();

#if Windows
        [DllImport("iec101x64d.dll", EntryPoint = "IEC101GetLibraryBuildTime", CallingConvention = System.Runtime.InteropServices.CallingConvention.StdCall)]
#elif Linux
     [DllImport("libx86_64-iec101.so")]
#endif
    public static extern System.IntPtr IEC101GetLibraryBuildTime();

#if Windows
        [DllImport("iec101x64d.dll", EntryPoint = "IEC101Create", CallingConvention = System.Runtime.InteropServices.CallingConvention.StdCall)]
#elif Linux
     [DllImport("libx86_64-iec101.so")]
#endif
    public static extern System.IntPtr IEC101Create(ref iec101types.sIEC101Parameters psParameters, ref short peErrorCode, ref short ptErrorValue);

#if Windows
        [DllImport("iec101x64d.dll", EntryPoint = "IEC101LoadConfiguration", CallingConvention = System.Runtime.InteropServices.CallingConvention.StdCall)]
#elif Linux
     [DllImport("libx86_64-iec101.so")]
#endif
    public static extern short IEC101LoadConfiguration(System.IntPtr myIEC101Obj, ref iec101types.sIEC101ConfigurationParameters psIEC101Config, ref short ptErrorValue);

#if Windows
        [DllImport("iec101x64d.dll", EntryPoint = "IEC101Start", CallingConvention = System.Runtime.InteropServices.CallingConvention.StdCall)]
#elif Linux
     [DllImport("libx86_64-iec101.so")]
#endif
    public static extern short IEC101Start(System.IntPtr myIEC101Obj, ref short ptErrorValue);

#if Windows
        [DllImport("iec101x64d.dll", EntryPoint = "IEC101SetDebugOptions", CallingConvention = System.Runtime.InteropServices.CallingConvention.StdCall)]
#elif Linux
     [DllImport("libx86_64-iec101.so")]
#endif
    public static extern short IEC101SetDebugOptions(System.IntPtr myIEC101Obj, ref iec101types.sIEC101DebugParameters psDebugParams, ref short ptErrorValue);

#if Windows
        [DllImport("iec101x64d.dll", EntryPoint = "IEC101Stop", CallingConvention = System.Runtime.InteropServices.CallingConvention.StdCall)]
#elif Linux
     [DllImport("libx86_64-iec101.so")]
#endif
    public static extern short IEC101Stop(System.IntPtr myIEC101Obj, ref short ptErrorValue);

#if Windows
        [DllImport("iec101x64d.dll", EntryPoint = "IEC101Free", CallingConvention = System.Runtime.InteropServices.CallingConvention.StdCall)]
#elif Linux
     [DllImport("libx86_64-iec101.so")]
#endif
    public static extern short IEC101Free(System.IntPtr myIEC101Obj, ref short ptErrorValue);

#if Windows
        [DllImport("iec101x64d.dll", EntryPoint = "IEC101Update", CallingConvention = System.Runtime.InteropServices.CallingConvention.StdCall)]
#elif Linux
     [DllImport("libx86_64-iec101.so")]
#endif
    public static extern short IEC101Update(System.IntPtr myIEC101Obj, byte bCreateEvent, ref iec101types.sIEC101DataAttributeID psDAID, ref iec101types.sIEC101DataAttributeData psNewValue, ushort u16Count, ref short ptErrorValue);

#if Windows
        [DllImport("iec101x64d.dll", EntryPoint = "IEC101Read", CallingConvention = System.Runtime.InteropServices.CallingConvention.StdCall)]
#elif Linux
     [DllImport("libx86_64-iec101.so")]
#endif
    public static extern short IEC101Read(System.IntPtr myIEC101Obj, ref iec101types.sIEC101DataAttributeID psDAID, ref iec101types.sIEC101DataAttributeData psReturnedValue, ref short ptErrorValue);

#if Windows
        [DllImport("iec101x64d.dll", EntryPoint = "IEC101Write", CallingConvention = System.Runtime.InteropServices.CallingConvention.StdCall)]
#elif Linux
     [DllImport("libx86_64-iec101.so")]
#endif
    public static extern short IEC101Write(System.IntPtr myIEC101Obj, iec60870common.eCounterFreezeFlags eCounterFreeze, ref iec101types.sIEC101DataAttributeID psDAID, ref iec101types.sIEC101DataAttributeData psWriteValue, ref iec101types.sIEC101WriteParameters ptWriteParams, ref short ptErrorValue);

#if Windows
        [DllImport("iec101x64d.dll", EntryPoint = "IEC101Select", CallingConvention = System.Runtime.InteropServices.CallingConvention.StdCall)]
#elif Linux
     [DllImport("libx86_64-iec101.so")]
#endif
    public static extern short IEC101Select(System.IntPtr myIEC101Obj, ref iec101types.sIEC101DataAttributeID psDAID, ref iec101types.sIEC101DataAttributeData psSelectValue, ref iec101types.sIEC101CommandParameters psSelectParams, ref short ptErrorValue);

#if Windows
        [DllImport("iec101x64d.dll", EntryPoint = "IEC101Operate", CallingConvention = System.Runtime.InteropServices.CallingConvention.StdCall)]
#elif Linux
     [DllImport("libx86_64-iec101.so")]
#endif
    public static extern short IEC101Operate(System.IntPtr myIEC101Obj, ref iec101types.sIEC101DataAttributeID psDAID, ref iec101types.sIEC101DataAttributeData psOperateValue, ref iec101types.sIEC101CommandParameters psOperateParams, ref short ptErrorValue);

#if Windows
        [DllImport("iec101x64d.dll", EntryPoint = "IEC101SelectBeforeOperate", CallingConvention = System.Runtime.InteropServices.CallingConvention.StdCall)]
#elif Linux
     [DllImport("libx86_64-iec101.so")]
#endif
    public static extern short IEC101SelectBeforeOperate(System.IntPtr myIEC101Obj, ref iec101types.sIEC101DataAttributeID psDAID, ref iec101types.sIEC101DataAttributeData psSelectValue, ref iec101types.sIEC101CommandParameters psSelectParams, ref short ptErrorValue);

#if Windows
        [DllImport("iec101x64d.dll", EntryPoint = "IEC101Cancel", CallingConvention = System.Runtime.InteropServices.CallingConvention.StdCall)]
#elif Linux
     [DllImport("libx86_64-iec101.so")]
#endif
    public static extern short IEC101Cancel(iec60870common.eOperationFlag eOperation, System.IntPtr myIEC101Obj, ref iec101types.sIEC101DataAttributeID psDAID, ref iec101types.sIEC101DataAttributeData psCancelValue, ref iec101types.sIEC101CommandParameters psCancelParams, ref short ptErrorValue);

#if Windows
        [DllImport("iec101x64d.dll", EntryPoint = "IEC101GetDataTypeAndSize", CallingConvention = System.Runtime.InteropServices.CallingConvention.StdCall)]
#elif Linux
     [DllImport("libx86_64-iec101.so")]
#endif
    public static extern short IEC101GetDataTypeAndSize(System.IntPtr myIEC101Obj, ref iec101types.sIEC101DataAttributeID psDAID, ref iec101types.sIEC101DataAttributeData psReturnedValue, ref short ptErrorValue);

#if Windows
        [DllImport("iec101x64d.dll", EntryPoint = "IEC101ParameterAct", CallingConvention = System.Runtime.InteropServices.CallingConvention.StdCall)]
#elif Linux
     [DllImport("libx86_64-iec101.so")]
#endif
    public static extern short IEC101ParameterAct(System.IntPtr myIEC101Obj, ref iec101types.sIEC101DataAttributeID psDAID, ref iec101types.sIEC101DataAttributeData psOperateValue, ref iec101types.sIEC101ParameterActParameters psParaParams, ref short ptErrorValue);

#if Windows
        [DllImport("iec101x64d.dll", EntryPoint = "IEC101ClientStatus", CallingConvention = System.Runtime.InteropServices.CallingConvention.StdCall)]
#elif Linux
     [DllImport("libx86_64-iec101.so")]
#endif
    public static extern short IEC101ClientStatus(System.IntPtr myIEC101Obj, ref iec101types.sIEC101DataAttributeID psDAID, ref iec60870common.eStatus peSat, ref short ptErrorValue);

#if Windows
        [DllImport("iec101x64d.dll", EntryPoint = "IEC101GetFile", CallingConvention = System.Runtime.InteropServices.CallingConvention.StdCall)]
#elif Linux
     [DllImport("libx86_64-iec101.so")]
#endif
    public static extern short IEC101GetFile(System.IntPtr myIEC101Obj, ref iec101types.sIEC101DataAttributeID psDAID, ushort u16FileName, ref short ptErrorValue);

#if Windows
        [DllImport("iec101x64d.dll", EntryPoint = "IEC101ListDirectory", CallingConvention = System.Runtime.InteropServices.CallingConvention.StdCall)]
#elif Linux
     [DllImport("libx86_64-iec101.so")]
#endif
    public static extern short IEC101ListDirectory(System.IntPtr myIEC101Obj, ref iec101types.sIEC101DataAttributeID psDAID, ref short ptErrorValue);

#if Windows
        [DllImport("iec101x64d.dll", EntryPoint = "GetIEC101ObjectStatus", CallingConvention = System.Runtime.InteropServices.CallingConvention.StdCall)]
#elif Linux
     [DllImport("libx86_64-iec101.so")]
#endif
    public static extern short GetIEC101ObjectStatus(System.IntPtr myIEC101Obj, ref tgtcommon.eAppState peCurrentState, ref short ptErrorValue);

#if Windows
        [DllImport("iec101x64d.dll", EntryPoint = "IEC101ErrorCodeString", CallingConvention = System.Runtime.InteropServices.CallingConvention.StdCall)]
#elif Linux
     [DllImport("libx86_64-iec101.so")]
#endif
    public static extern void IEC101ErrorCodeString(ref iec101types.sIEC101ErrorCode psIEC101ErrorCodeDes);

#if Windows
        [DllImport("iec101x64d.dll", EntryPoint = "IEC101ErrorValueString", CallingConvention = System.Runtime.InteropServices.CallingConvention.StdCall)]
#elif Linux
     [DllImport("libx86_64-iec101.so")]
#endif
    public static extern void IEC101ErrorValueString(ref iec101types.sIEC101ErrorValue psIEC101ErrorValueDes);

#if Windows
        [DllImport("iec101x64d.dll", EntryPoint = "IEC101GetLibraryLicenseInfo", CallingConvention = System.Runtime.InteropServices.CallingConvention.StdCall)]
#elif Linux
     [DllImport("libx86_64-iec101.so")]
#endif
    public static extern System.IntPtr IEC101GetLibraryLicenseInfo();

}

