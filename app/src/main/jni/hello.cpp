#include <cstdint>
#include <jni.h>

// for native asset manager
#include <sys/types.h>
#include <android/log.h>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>

#include <string>
#include <vector>
#include <sstream>
#include <iomanip>

extern "C" {

    struct LatLng {
        double lat;
        double lng;
    };

    struct Node {
        double lat;
        double lng;
    };

    std::vector<Node> getNodes(JNIEnv* env, jobject assetManager) {

        std::vector<Node> result;

        AAssetManager* mgr = AAssetManager_fromJava(env, assetManager);

        AAsset* asset = AAssetManager_open(mgr, "nodes.csv", AASSET_MODE_UNKNOWN);
        if (asset) {

            size_t len = AAsset_getLength(asset);

            char* buff = (char*) malloc(len + 1);
            AAsset_read(asset, buff, len);
            buff[len] = 0;

            std::string str = "";
            int j = 0;

            Node firstNode;
            result.push_back(firstNode);
            int idx = 0;

            for (int i=0; i<len; i++) {
                if (buff[i] == '\n') {
                    str.clear();

                    Node newNode;
                    result.push_back(newNode);
                    idx++;

                    j = 0;

                } else if (buff[i] == ',') {
                    switch (j) {
                        case 0:
                            result[idx].lat = atof(str.c_str());
                            break;
                        case 1:
                            result[idx].lng = atof(str.c_str());
                            break;
                        default:
                            break;
                    }
                    str.clear();
                    j++;
                } else {
                    str += buff[i];
                };
            }

            AAsset_close(asset);
            free(buff);
        } else {
            __android_log_print(ANDROID_LOG_ERROR, "Test Asset Manager", "Cannot open file");
        }

        return result;
    }

    jstring Java_com_exsample_toyomoly_ndksample_SearchRouteCpp_calcByCpp(JNIEnv* env, jobject obj, jobject assetManager,
            jdouble stLat, jdouble stLng, jdouble edLat, jdouble edLng) {

        std::vector<Node> nodes = getNodes(env, assetManager);

        // 文字列の組み立て
        std::stringstream ss;
        ss << std::fixed << std::setprecision(6);
        ss << "[" << stLat << ", " << stLng << "]";

        for (int i=0; i<nodes.size(); i++) {
            ss << ",[" << nodes[i].lat << ", " << nodes[i].lng << "]";
        }

        ss << ",[" << edLat << ", " << edLng << "]";

        jstring result = env -> NewStringUTF(ss.str().c_str());
        return result;

    }

}